//xjf add
#pragma once
#include <string>
#include <functional>
#include <map>
#include "log.h"
#include "mongoose.h"

using callback_prototype = void(*)(struct mg_connection* c, int ev, void* ev_data);
struct HttpServerConnect {
    std::string listen_url;
    callback_prototype callback ;
};

class MgHttpServer {
public:

    MgHttpServer(std::vector<HttpServerConnect> vec_connect, const int listen_timeout_ms, const int poll_timeout_ms)
        : vec_connect_(vec_connect), listen_timeout_ms_(listen_timeout_ms), poll_timeout_ms_(poll_timeout_ms) , is_running_(false), to_stop_(false){};

    ~MgHttpServer() { to_stop(); };
    
public:

    //block
    void launch();
    //nonblock
    void to_stop();
    //for outside fetch status
    bool is_running();

private:

    void do_connect_();
    int check_connect_info_();
    
  
    std::vector<HttpServerConnect> vec_connect_;
    int listen_timeout_ms_;
    int poll_timeout_ms_;

    bool to_stop_;
    bool is_running_;
};

//test handle
inline void mg_http_server_cb_file_proxy(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        SLOGD("enter callback1 file proxy");
        struct mg_http_message *hm = (mg_http_message*)ev_data, tmp = {0};
        struct mg_str unknown = mg_str_n("?", 1);
        struct mg_str * cl;
        struct mg_http_serve_opts opts = { 0 };
        opts.root_dir = ".";
        opts.ssi_pattern = "#.html";
        mg_http_serve_dir(c, hm, &opts);
        mg_http_parse((char *) c->send.buf, c->send.len, &tmp);
        cl = mg_http_get_header(&tmp, "Content-Length");
        if (cl == NULL) cl = &unknown;
        MG_INFO(("%.*s %.*s %.*s %.*s", (int) hm->method.len, hm->method.ptr,
                (int) hm->uri.len, hm->uri.ptr, (int) tmp.uri.len, tmp.uri.ptr,
                (int) cl->len, cl->ptr));
    }
};

inline void mg_http_server_cb_message_print(struct mg_connection *c, int ev, void *ev_data) {
        if (ev == MG_EV_HTTP_MSG) {
            SLOGD("enter callback2 message print");
            struct mg_http_message *hm = (mg_http_message*)ev_data, tmp = {0};
            SLOGI("get http message:\n{}", std::string(hm->message.ptr, hm->message.len));
        }
    };