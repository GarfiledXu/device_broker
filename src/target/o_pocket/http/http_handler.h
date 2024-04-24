//xjf add
#pragma once
#include <functional>
#include <string>
#include <list>
#include "mongoose.h"

struct RequestInfo {
    mg_http_message* hm;
    // uint32_t sender_ip;
    uint8_t sender_ip[16];
    uint16_t sender_port;
    uint8_t listener_ip[16];
    uint16_t listener_port;
    std::unique_ptr<std::string> sender_ip_port_str;
    std::unique_ptr<std::string> sender_ip_str;
    std::unique_ptr<std::string> sender_port_str;
    std::unique_ptr<std::string> listener_ip_port_str;
    std::unique_ptr<std::string> listener_ip_str;
    std::unique_ptr<std::string> listener_port_str;

    std::string method;
    std::string uri;
    std::string body;
};
struct ResponseInfo {
    int errcode;
    std::string header;
    std::string body;
};
struct ResponseHeader {
    std::string key;
    std::string value;
};

struct Router {
    Router(bool in_enable, std::unique_ptr<std::string> in_name, float in_priority)
        :enable_(in_enable), name(std::move(in_name)),register_priority(in_priority) {};
    float register_priority = 0.0f;
    bool enable_ = true;
    std::unique_ptr<std::string> name = nullptr;
    //return 0, to response
    virtual int http_msg_accept(const RequestInfo& request_info,  ResponseInfo& reponse_info) = 0;
};

class MgHttpServerHandler {
public:
    ~MgHttpServerHandler() = default;
    static MgHttpServerHandler& ins() {
        static MgHttpServerHandler static_ins;
        return static_ins;
    }
private:
    MgHttpServerHandler() = default; 

public:
    static std::string reponse_header_splice(std::list<ResponseHeader> input_header_list);
    static void output_uniform_callback(struct mg_connection* c, int ev, void* ev_data);
    static void request_response_info_print(const RequestInfo& , const ResponseInfo&);

    template<typename T>
    static Router* static_register_and_add_router();

    std::list<Router*>& router_list();
    bool router_list_check();

private:
    std::list<Router*> router_list_;
};

template<typename T>
Router* MgHttpServerHandler::static_register_and_add_router() {
    Router* new_ptr = new T();
    auto& cur_list = MgHttpServerHandler::ins().router_list();
    cur_list.push_back(new_ptr);
    cur_list.sort([](Router*& r1, Router*& r2) {return r1->register_priority < r2->register_priority;});
    return new_ptr;
}
#define IMPL_HTTP_ROUTER(name, enable) \ 
IMPL_HTTP_ROUTER_P(name, enable, 0.0f)

#define IMPL_HTTP_ROUTER_P(name, enable, priority) \
class impl_router_##name : public Router{ \
public: \
    impl_router_##name():Router(enable, enable?std::unique_ptr<std::string>(new std::string(#name)) : nullptr, priority){}; \
    static Router* static_ins; \
    virtual int http_msg_accept(const RequestInfo& in_request_info,  ResponseInfo& out_reponse_info) override; \
}; \
Router* impl_router_##name::static_ins = MgHttpServerHandler::static_register_and_add_router<impl_router_##name>(); \
int impl_router_##name::http_msg_accept(const RequestInfo& in_request_info,  ResponseInfo& out_reponse_info) 

#include "http_handler_help_macro.h"

inline std::unique_ptr<std::string> get_ip_str(struct mg_addr& addr) {
    char buf[100];
    mg_snprintf(buf, sizeof(buf), "%M", mg_print_ip, &addr);  
    return std::unique_ptr<std::string>(new std::string(buf));
}

inline std::unique_ptr<std::string> get_port_str(struct mg_addr& addr) {
    char buf[100];
    return std::unique_ptr<std::string>(new std::string(std::to_string(mg_ntohs(addr.port))));
}

inline uint16_t get_port_value(struct mg_addr& addr) {
    char buf[100];
    return mg_ntohs(addr.port);
}

inline std::unique_ptr<std::string> get_ip_port_str(struct mg_addr& addr) {
    char buf[100];
    mg_snprintf(buf, sizeof(buf), "%M", mg_print_ip_port, &addr);  
    return std::unique_ptr<std::string>(new std::string(buf));
}

inline void request_info_load(RequestInfo& request_info, mg_http_message *hm, mg_connection* c) {
    request_info.hm = hm;
    memcpy(request_info.sender_ip, reinterpret_cast<char*>(c->rem.ip), sizeof(c->rem.ip));
    request_info.sender_port = get_port_value(c->rem);
    memcpy(request_info.listener_ip, reinterpret_cast<char*>(c->loc.ip), sizeof(c->loc.ip));
    request_info.listener_port = get_port_value(c->loc);

    request_info.sender_ip_port_str = get_ip_port_str(c->rem);
    request_info.sender_port_str = get_port_str(c->rem);
    request_info.sender_ip_str = get_ip_str(c->rem);

    request_info.listener_ip_port_str = get_ip_port_str(c->loc);
    request_info.listener_port_str = get_port_str(c->loc);
    request_info.listener_ip_str = get_ip_str(c->loc);

    request_info.method = std::string(hm->method.ptr, hm->method.len);
    request_info.uri = std::string(hm->uri.ptr, hm->uri.len); 
    request_info.body = std::string(hm->body.ptr, hm->body.len);  

    return;
}


