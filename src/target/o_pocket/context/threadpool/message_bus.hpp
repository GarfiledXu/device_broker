#ifndef GF_MESSAGE_BUS_HPP
#define GF_MESSAGE_BUS_HPP
#include "my-internal.h"

/**
 *@brief for set msg listen process
 * @tparam Tchannel 
 * @tparam Tmsg 
 */

/*
template<typename Tchannel, typename Tmsg>
class Listener {
public:
    using UniMsg = std::unique_ptr<Tmsg>;
    using Callback = std::function<void(const Tchannel&, UniMsg)>;
    //explicit Listener(const Tchannel& channel) {
        //LOG_DEBUG("Listener construct!\n");
    //};
    Listener() {};
    Listener(Callback&& callback) {
        LOG_DEBUG("Listener construct!\n");
        //std::lock_guard<std::mutex> lg(mutex_switch_callback_);
        on_handle_message_ = callback;
        //channel_ = channel;
    }
    virtual ~Listener() {
        LOG_DEBUG("Listener destruct!\n");
    };
    //void bind(Callback&& callback) {
        //LOG_DEBUG("Listener checkout callback!\n");
        //std::lock_guard<std::mutex> lg(mutex_switch_callback_);
        //on_handle_message_ = callback;
    //}
    GF_CLASS_DELETE_COPY(Listener);
    GF_CLASS_DELETE_MOVE(Listener);
private:
    friend class MessageBus<Tchannel, Tmsg>;
    friend void RegisterMsgListener();
    handle_message(const Tchannel& channel, UniMsg uni_msg) {
        LOG_DEBUG("Listener handle_message enter!\n");
        //std::lock_guard<std::mutex> lg(mutex_switch_callback_);
        if (on_handle_message_.operator bool())
            on_handle_message_(channel, std::move(uni_msg));
        else
            LOG_EXTR("Listener handle_message no callback ojb exsit!\n");
        LOG_DEBUG("Listener handle_message out!\n");
    };
    std::mutex mutex_switch_callback_;
    Callback on_handle_message_;
    //Tchannel channel_;
};
*/
 /*@brief 总线的意义，就是大家通过总线对象发布消息，在执行消息发布的同时根据类别信息总线遍历消息列表，执行符合的回调
    消息-回调-主题(类别)
    主题是在执行相关操作时，自动增加，还是通过专门的注册接口, 进行注册限制，来防止预期外操作, 还是提供选项？
      
 * @tparam Tchannel 
 * @tparam Tmsg 
 */
template<typename Tchannel, typename Tmsg>
class MessageBus {
public:
    using ShareMsg = std::shared_ptr<Tmsg>;
    using Listener_ = std::function<void(Tchannel, ShareMsg)>;
    using Listener = std::shared_ptr<Listener_>;
    using ListenerSet = std::set<Listener >;
    using ListenerVec = std::vector<Listener>;
    using ListenerMap = std::map<Tchannel,  ListenerSet>;
    using ChannelSet = std::set<Tchannel>;

    MessageBus(const bool is_strict_channel = true, const std::string& tag = "null") :
        is_strict_channel_(is_strict_channel), tag_(tag) {
    };
    virtual ~MessageBus() {};
    GF_CLASS_DELETE_COPY(MessageBus);
    int post(Tchannel channel, ShareMsg msg) {
        /**
         *@brief need check if channel exist, when strict mode and 
         when strict mode need check if channel have listener!
         */
        if (!check_channel_(channel))
            return -1;
        bool is_have_listener = false;
        auto& listener_set = listener_map_[channel];
        LOG_DEBUG("post listener, size:%d\n", listener_map_[channel].size());
        for (auto& listener : listener_set) {
            (*listener)(channel, msg);
            is_have_listener = true;
        }
        if (!is_have_listener)
            return -2;
        else
            return -1;
    };
    void broadcast(ShareMsg msg) {
        /**
         *@brief no channel check
         * @param listener_map_ 
         */
        for (auto& item : listener_map_) {
            for (auto& listener : item.second){
                (*listener)(item.first, msg);
            }
        }
        return;
    };
    int channel_register(Tchannel channel) {
        /**
         *@brief strct mode, if return true,  that is  retur error
         */
        if (check_channel_(channel)) 
            return -1;
        channel_set_.insert(channel);
        return 0;
    };
    int channel_cancel(Tchannel channel) {
        /**
         *@brief need return error, when target channel is not exist
         */
        if (channel_set_.find(channel) == channel_set_.end())
            return -1;
        channel_set_.erase(channel);
        return 0;
    }
    int listener_attach(Tchannel channel, Listener listener) {
        /**
         *@brief need check whether channel is exist when using strict mode
         */
        if (!check_channel_(channel))
            return -1;
        // ListenerSet listener_set;
        // std::set<std::shared_ptr<Listener>> listener_set;
        
        // std::vector<Listener> listeners;
        // listeners.push_back(listener);
        // listener_set.insert(std::make_shared<Listener>(listener));
        //listener_map_.emplace(channel, listener_set);
        listener_map_[channel].insert(listener);
        LOG_DEBUG("attach listener, size:%d\n", listener_map_[channel].size());
            
        return 0;
    };
    int listener_detach(Tchannel channel, const Listener& listener) {
        /**
         *@brief need check whether channel is exist, not only strict mode but alse not strict mode
         when iterator result is false, it mean channel not exist when mode is strict 
         */
        if (!check_channel_(channel))
            return -1;
        ListenerSet& listener_set = listener_map_[channel];
        bool is_find = false;
        for (auto it = listener_set.begin(); it != listener_set.end();) {
            if (*it == listener) {
                it = listener_set.erase(it);
                is_find = true;
            }
            else
                ++it;
        }
        if (!is_find)
            return -2;
        return 0;
    };
    
    //overload []
    //sample: msgbus[channel_1] = 
    
    

private:
    bool is_strict_channel_;
    const std::string tag_;
    ListenerMap listener_map_;
    ChannelSet channel_set_;
    std::mutex channel_mutex_;
    /**
     *@brief if return true:1、not strict mode 2、is strict mode and find item, if return false:is strict mode and not find item
        it's explicit that when return false, it's strict mode not match channel
     * @param channel 
     * @return true 
     * @return false 
     */
    bool check_channel_(Tchannel channel) {
        if (is_strict_channel_) {
            std::lock_guard<std::mutex> lg(channel_mutex_);
            if (channel_set_.find(channel) == channel_set_.end()) {
                return false;
            }
        }   
        return true;
    }
};
inline void test_message_bus() {
    using ShareMsg = std::shared_ptr <std::function<int()>>;
    using Listener = std::function<void(int, ShareMsg)>;
    MessageBus<int, std::function<int()>> msgbus(true, "msg");
    msgbus.channel_register(1);
    msgbus.channel_register(2);
    msgbus.channel_register(3);
    std::function<void (int, ShareMsg)> function1 = [](int channel, ShareMsg func) {
        auto fff = *(func.get());
        int value = fff();
        std::cout << "1 listener: " << channel << "get value:"  << fff() <<std::endl;
    };
    msgbus.listener_attach(1, std::make_shared<Listener>(function1));
     msgbus.listener_attach(2, std::make_shared<Listener>([](int channel, std::shared_ptr<std::function<int()> > func) {
        auto fff = *(func.get());
        int value = fff();
        std::cout << "2 listener: " << channel << "get value:"<< value <<std::endl;
        }));
      msgbus.listener_attach(3, std::make_shared<Listener>([](int channel, std::shared_ptr<std::function<int()> > func) {
        auto fff = *(func.get());
        int value = fff();
        std::cout << "3 listener: " << channel << "get value:"<< value <<std::endl;
        }));
      msgbus.broadcast(std::make_shared<std::function<int()>>([]() {return 1;}));
      msgbus.broadcast(std::make_shared<std::function<int()>>([]() {return 2;}));
      msgbus.broadcast(std::make_shared<std::function<int()>>([]() {return 3;}));
      msgbus.post(1, std::make_shared<std::function<int()>>([]() {return 11;}));
      msgbus.post(2, std::make_shared<std::function<int()>>([]() {return 22;}));
      msgbus.post(3, std::make_shared<std::function<int()>>([]() {return 33;}));
       
}
#if 0
//消息的过滤应该在
template<typename Tchannel, typename Tmsg>
class MessageBus {
public:
    using ShaMsg = std::shared_ptr<Tmsg>;
    using MsgQueue = std::shared_ptr<SafeQueue<Tmsg>>;
    using Listener = std::function<int(Tchannel*, Tmsg)>; //using Listener = std::function<int(Tchannel*, ShaMsg)>;
    using MqMap = std::unordered_map<Tchannel, MsgQueue>;
    // using ListShaMsg = std::vector<ShaMsg>;
    using ListenerVec = std::vector<Listener>;
    using ListenerMap = std::unordered_map<Tchannel, ListenerVec>;
    //using ChannelList = std::list<Tchannel>;
    using ChannelSet = std::unordered_set<Tchannel>;
    // using ListenerMap = std::unordered_map<>

    MessageBus(int msgqueue_len_ = 10, const bool is_strict_channel = true, const std::string& tag = "null") 
            :is_strict_channel_(is_strict_channel), nochannel_mq_que_(std::make_shared<SafeQueue<Tmsg>>(msgqueue_len_)) {
        obj_id_ = assign_obj_id();    
    }
    virtual  ~MessageBus() {};
    
    int post_to_listener(Tmsg sha_msg, const Tchannel* channel) {
        if (check_channel_(channel)) 
            return -1;
        std::lock_guard<std::mutex> lg(listener_mutex_);
        if (channel == nullptr) {
            for (auto& listener : nochannel_listener_vec_) {
                listener(channel, sha_msg);
            }
            for (auto& item : listener_map_) {
                item.second(channel, sha_msg);
            }
            return 0;
        }
        if (listener_map_.count(*channel)) {
            return -2;
        }
        listener_map_[*channel](channel, sha_msg);
        return 0;
    }

    // int post_to_listener_mq(Tmsg sha_msg, const Tchannel* channel) {
    //     if (check_channel_(channel))
    //         return -1;
    //     if (post_to_listener(sha_msg, channel)) {
    //         return -2;
    //     }
    //     if (post_to_mq(sha_msg, channel)) {
    //         return -3;
    //     }
    // }

    int post_to_mq(Tmsg sha_msg, const Tchannel* channel) {
        if (check_channel_(channel))
            return -1;
        std::lock_guard<std::mutex> lg(listener_mutex_);
        if (channel == nullptr) {
            for (auto& item : mq_map_){
                item.second->push_sync(sha_msg);
            }
            nochannel_mq_que_->push_sync(sha_msg);
            return 0;
        }
        if (mq_map_.find(*channel) == mq_map_.end())
            return -2;
        mq_map_[*channel]->push_sync(sha_msg);
        return 0;
    }

    MsgQueue get_mq(const Tchannel* channel) {
        if (check_channel_(channel))
            return nullptr;
        if (channel == nullptr) {
            return nochannel_mq_que_;
        }
        return mq_map_[*channel];
    }

    int fetch_mq_msg_sync(const Tchannel* channel, Tmsg& msg) {
        if (check_channel_(channel))
            return -1;
        if(channel == nullptr){
            nochannel_mq_que_->pop_sync(msg);
            return 0;
        }
        MsgQueue mq = get_mq(channel);
        if(!mq){
            return -2;
        }
        mq->pop_sync(msg);
        return 0;
    }

    int register_channel(const Tchannel* channel) {
        if (channel == nullptr) {
            return -1;
        }
        channel_set_.insert(*channel);
        mq_map_[*channel] = std::make_shared<SafeQueue<Tmsg>>(msgqueue_len_);
        return 0;
    }

    ChannelSet get_channel_set() {
        std::lock_guard<std::mutex> lg(channel_mutex_);
        return channel_set_;
    }

    // int attach_listener(const Listener& listener, const Tchannel* channel) {
    //     if (check_channel_(channel))
    //         return -1;
    //     std::lock_guard<std::mutex> lg(listener_mutex_);
    //     if (channel == nullptr) {
    //         nochannel_listener_vec_.push_back(listener);
    //         return 0;
    //     }
    //    listener_map_[*channel].push_back(listener);
    //     return 0;
    // }

    // int detach_listener(const Listener& listener) {
    //     auto func_remove_listener = [&](const ListenerVec& lis_vec, const Listener& lis) {
    //         auto& listener_vec = lis_vec;
    //         listener_vec.erase(std::remove_if(listener_vec.begin(), listener_vec.end(),
    //             [&](const Listener& l) {
    //                 return &l == &lis_vec;
    //             }), listener_vec.end());
    //     };
    //     std::lock_guard<std::mutex> lg(listener_mutex_);
    //     for (auto& item : listener_map_) {
    //         auto& listener_vec = item.second;
    //         func_remove_listener(listener_vec, listener);
    //     }
    //     func_remove_listener(nochannel_listener_vec_, listener);
    //     return 0;
    // }
    size_t get_obj_id() { return obj_id_;}
    GF_CLASS_DELETE_COPY(MessageBus);
private:
    friend void RegisterMsgBus();
    friend void RegisterMsgChannel();
    bool is_strict_channel_;
    MqMap mq_map_;
    // ListenerMap listener_map_;
    //ChannelList channelList_;
    ChannelSet channel_set_;
    MsgQueue nochannel_mq_que_;
    int  msgqueue_len_;
    // ListenerVec nochannel_listener_vec_;

    size_t obj_id_;
    std::mutex listener_mutex_;
    std::mutex channel_mutex_;
    static size_t assign_obj_id() {
        static std::mutex obj_id_mutex;
        static size_t obj_count = 0;
        std::lock_guard<std::mutex> lg(obj_id_mutex);
        return obj_count;
    }
    int check_channel_(const Tchannel* channel) {
        if(channel == nullptr)
            return 0;
        if (is_strict_channel_ && (channel)) {
            std::lock_guard<std::mutex> lg(channel_mutex_);
            if (channel_set_.find(*channel) != channel_set_.end()) {
                return 0;
            }
        }
        // LOG_ERROR("strict channel, current channel been registered in channel set!\n");
        return -1;
    }
public:
    class Callback {
    public:
        virtual void onBussConstruct(){};
        virtual void onBussDestruct(){};
        virtual void onPost() {};
        virtual void onListener() {};
    };
};


#endif
#endif