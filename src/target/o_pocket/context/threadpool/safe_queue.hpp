#ifndef GF_SAFE_QUEUE_HPP
#define GF_SAFE_QUEUE_HPP
#include "my-internal.h"

/**
 * 
 *@brief need addition iterate insert operation 2023/05/30
 need add dynamic set length of queue
 dynamic adjustment of length upper limit strategy:-->
increase limit, just modify limit_len_max_
decrease limit if actual length <= expect limit length, modify length directly else still same until consumer take item, actual length will resume

update record:
2023/05/31 add dynamic adjust limit length, by xjf2613
 * @tparam T_item
 */
template<typename T_item>
class SafeQueue {
public:
    using InnerQueue = std::list<T_item>;
    //push item
    int try_push(const T_item& value, const long timeout_ms) {
        return inner_try_push_(value, timeout_ms);
    };
    int try_push(T_item&& value, const long timeout_ms) {
        return inner_try_push_(std::forward<T_item>(value), timeout_ms);
    };
    void push_sync(const T_item& lv) {
        inner_push_sync_(lv);
    };
    void push_sync(T_item&& rv) {
        inner_push_sync_(std::forward<T_item>(rv));
    };
    int push_async(const T_item& lv) {
        return inner_push_async_(lv);
    };
    int push_async(T_item&& rv) {
        return inner_push_async_(std::forward<T_item>(rv));
    };
    //pop item
    int try_pop(T_item& lv, const long timeout_ms) {
        return inner_try_pop_(lv, timeout_ms);
    }
    void pop_sync(T_item& lv) {
        inner_pop_sync_(lv);
    }
    int pop_async(T_item& lv) {
        return inner_pop_async_(lv);
    }
    //pop list
    int try_pop_list(std::list<T_item>& ll, const long timeout_ms) {
        return inner_try_pop_list_(ll, timeout_ms);
    }
    void pop_sync_list(std::list<T_item>& ll) {
        inner_pop_sync_list_(ll);
    }
    int pop_async_list(std::list<T_item>& ll) {
        return inner_pop_async_list_(ll);
    }

    const InnerQueue get_inner_queue(){
        return inner_queue_;
    }
    //insert item
    /**
     *@brief xjf2613 2023/05/30 add
     when predicate return true, correspond to insert item!
     */
    using InsertPredicate = std::function<bool(T_item&)>;
    int try_insert(const T_item& value, const long timeout_ms, InsertPredicate&& predicate) {
        return inner_try_insert_(value, timeout_ms, std::move(predicate));
    };
    int try_insert(T_item&& value, const long timeout_ms, InsertPredicate&& predicate) {
        return inner_try_insert_(std::forward<T_item>(value), timeout_ms, std::move(predicate));
    };
    void insert_sync(const T_item& value, InsertPredicate&& predicate) {
        inner_insert_sync_(value, std::move(predicate));
    }
    void insert_sync(T_item&& value, InsertPredicate&& predicate) {
        inner_insert_sync_(std::forward<T_item>(value), std::move(predicate));
    }
    int insert_async(const T_item& value, InsertPredicate&& predicate) {
        return inner_insert_async_(value, predicate);
    }
    int insert_async(T_item&& value, InsertPredicate&& predicate) {
        return inner_insert_async_(std::forward<T_item>(value), predicate);
    }

    //property
    size_t get_size() {
        return size_();
    };
    size_t count(T_item& item) {
        std::unique_lock<std::mutex> ul(mutex_);
        return std::count_if(inner_queue_.begin(), inner_queue_.end(), [&item](T_item& it) {
            return it == item;
            });
    };
    bool empty() {
        std::unique_lock<std::mutex> ul(mutex_);
        return inner_queue_.empty();
    };
    //iterator
    //control
    void stop() {
        inner_stop_();
    };
    int clear() {
        std::unique_lock<std::mutex> ul(mutex_);
        inner_queue_.clear();
        return 0;
    };
    int reset() {
        if (clear()) {
            return -1;
        }
        is_stop_flag_.store(false);
        return 0;
    }
    /**
     *@brief xjf2613 2023/05/31 add
     */
    void change_limit_len_max(const size_t expect_value) {
        limit_len_max_.store(expect_value);
        return;
    }
    //for debug
    // void print(){
    //     LOG_DEBUG("print queue content:\n");
    //     for (auto& itm : inner_queue_) {
    //         printf("\n")
    //     }
    // }
    //construct
    virtual ~SafeQueue(){};
    SafeQueue(const size_t limit_len_max) : is_stop_flag_(false), limit_len_max_(limit_len_max){};
    GF_CLASS_DELETE_COPY(SafeQueue);
private:
    InnerQueue inner_queue_;
    std::condition_variable condition_push_, condition_pop_;
    std::mutex mutex_;
    std::atomic_bool is_stop_flag_;
    // const size_t limit_len_max_;
    std::atomic_size_t limit_len_max_;

    //inner operation 
    size_t size_() {
        std::unique_lock<std::mutex> ul(mutex_);
        return inner_queue_.size();
    }
    //for inner push
    //reference collapse
    template<typename T>
    void inner_push_sync_(T&& value) {
        std::unique_lock<std::mutex> ul(mutex_);
        condition_push_.wait(ul, [&]() {
            return (inner_queue_.size() < limit_len_max_.load()) || (is_stop_flag_);//already lock, shouldn't use size_();
            });
        if (is_stop_flag_) {
            return;
        }
        inner_queue_.push_back(std::forward<T>(value));
        condition_pop_.notify_one();//correspond to push one unit
    }
    template<typename T>
    int inner_try_push_(T&& value, const long timeout_ms) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (!condition_push_.wait_for(ul, std::chrono::milliseconds(timeout_ms),
                [&]() {return (inner_queue_.size() < limit_len_max_.load()) || (is_stop_flag_);//already lock, shouldn't use size_();
                    })
            ) {
            return -1;
        }
        if (is_stop_flag_) {
            return -2;
        }
        inner_queue_.push_back(std::forward<T>(value));
        condition_pop_.notify_one();//correspond to push one unit
        return 0;
    }
    template<typename T>
    int inner_push_async_(T&& value) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (is_stop_flag_ || (inner_queue_.size() >= limit_len_max_.load()))
            return -1;
        inner_queue_.push_back(std::forward<T>(value));
        condition_pop_.notify_one();//correspond to push one unit
        return 0;
    }
    //for inner pop 
    void inner_pop_sync_(T_item& out_value) {
        std::unique_lock<std::mutex> ul(mutex_);
        condition_pop_.wait(ul, [&]() {
            return (inner_queue_.size() > 0) || (is_stop_flag_);//already lock, shouldn't use size_();
            });
        if (is_stop_flag_) {
            return;
        }
        out_value = inner_queue_.front();
        inner_queue_.pop_front();
        condition_push_.notify_one();//correspond to pop one unit
    }   
    int inner_try_pop_(T_item& out_value, const long timeout_ms) {
        std::unique_lock<std::mutex> ul(mutex_);
        //already lock, shouldn't use size_(); when condition wait, will auto unlock mutex by unique_lock, when execute predicate, will lock again util execute finished;
        if (!condition_pop_.wait_for(ul, std::chrono::milliseconds(timeout_ms),
            [&]() {return (inner_queue_.size() > 0) || (is_stop_flag_);
            })
            ) {
            return -1;
        }
        if (is_stop_flag_) {
            return -2;
        }
        out_value = inner_queue_.front();
        inner_queue_.pop_front();
        condition_push_.notify_one();//correspond to pop one unit
        return 0;
    }    
    int inner_pop_async_(T_item& out_value) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (is_stop_flag_ || (inner_queue_.size() < 1))
            return -1;
        out_value = inner_queue_.front();
        inner_queue_.pop_front();
        condition_push_.notify_one();
        return 0;
    }
    void inner_pop_sync_list_(std::list<T_item>& out_list) {
        std::unique_lock<std::mutex> ul(mutex_);
        condition_pop_.wait(ul, [&]() {
            return (inner_queue_.size() > 0) || (is_stop_flag_);//already lock, shouldn't use size_();
            });
        if (is_stop_flag_) {
            return;
        }
        out_list = std::move(inner_queue_);
        inner_queue_.clear();
        condition_push_.notify_all();//corresppond to pop list
    }
    int inner_try_pop_list_(std::list<T_item>& out_list, const long timeout_ms) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (!condition_pop_.wait_for(ul, std::chrono::milliseconds(timeout_ms),
                [&]() {return (inner_queue_.size() > 0) || (is_stop_flag_);//already lock, shouldn't use size_();
                    })
            ) {
            return -1;
        }
        if (is_stop_flag_) {
            return -2;
        }
        out_list = std::move(inner_queue_);
        inner_queue_.clear();
        condition_push_.notify_all();//corresppond to pop list
        return 0;
    }   
    int inner_pop_async_list_(std::list<T_item>& out_list) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (is_stop_flag_ || (inner_queue_.size() < 1))
            return -1;
        out_list = std::move(inner_queue_);
        inner_queue_.clear();
        condition_push_.notify_all();
        return 0;
    }
    //inner stop
    void inner_stop_() {
        {
            std::unique_lock<std::mutex> ul(mutex_);
            is_stop_flag_.store(true);
        }
        condition_push_.notify_all();
        condition_pop_.notify_all();
    }
    /**
     *@brief xjf2613 2023/05/30 add
     */
    template<typename T>
    void inner_insert_sync_(T&& value, InsertPredicate&& predicate) {
        std::unique_lock<std::mutex> ul(mutex_);
        condition_push_.wait(ul, [&]() {
            return (inner_queue_.size() < limit_len_max_) || (is_stop_flag_);//already lock, shouldn't use size_();
            });
        if (is_stop_flag_) {
            return;
        }
        /**
         *@brief if not find, insert directly
         * @param it 
         */
        bool is_find_bigger = false;
        for (auto it = inner_queue_.begin(); it != inner_queue_.end();) {
            if (predicate(*it)) {
                inner_queue_.insert(it, std::forward<T>(value));
                is_find_bigger = true;
                break;
            }
            it++;
        }
        if (!is_find_bigger)
            inner_queue_.push_back(std::forward<T>(value));
        condition_pop_.notify_one();//correspond to push one unit
    }
    template<typename T>
    int inner_try_insert_(T&& value, const long timeout_ms, InsertPredicate&& predicate) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (!condition_push_.wait_for(ul, std::chrono::milliseconds(timeout_ms),
                [&]() {return (inner_queue_.size() < limit_len_max_) || (is_stop_flag_);//already lock, shouldn't use size_();
                    })
            ) {
            return -1;
        }
        if (is_stop_flag_) {
            return -2;
        }
        bool is_find_bigger = false;
        for (auto it = inner_queue_.begin(); it != inner_queue_.end();) {
            if (predicate(*it)) {
                inner_queue_.insert(it, std::forward<T>(value));
                is_find_bigger = true;
                break;
            }
            it++;
        }
        if (!is_find_bigger)
            inner_queue_.push_back(std::forward<T>(value));
        condition_pop_.notify_one();//correspond to push one unit
        return 0;
    }
    template<typename T>
    int inner_insert_async_(T&& value, InsertPredicate&& predicate) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (is_stop_flag_ || (inner_queue_.size() >= limit_len_max_))
            return -1;
        condition_pop_.notify_one();//correspond to push one unit
        bool is_find_bigger = false;
        for (auto it = inner_queue_.begin(); it != inner_queue_.end();) {
            if (predicate(*it)) {
                inner_queue_.insert(it, std::forward<T>(value));
                is_find_bigger = true;
                break;
            }
            it++;
        }
        if (!is_find_bigger)
            inner_queue_.push_back(std::forward<T>(value));
        return 0;
    }

};



#endif