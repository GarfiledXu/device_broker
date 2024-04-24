#include "http_server.h"
#include "json.hpp"
#include "signal_handle.h"



void MgHttpServer::launch() {
    if (is_running_) {
        SLOGW("http server already launch! will break current launch operation");
        return;
    }
    //reset flag
    is_running_ = true;
    //maybe assinged true before do connect
    // to_stop_ = false;

    do_connect_();

    is_running_ = false;
    to_stop_ = false;
}

void MgHttpServer::to_stop() {
    if (is_running_) {
        to_stop_ = true;
        return;
    }
    SLOGW("http server is not running, no need to stop");
}

bool MgHttpServer::is_running() {
    return is_running_;
}

int MgHttpServer::check_connect_info_() {
    for (auto& cur_connect_info : vec_connect_) {
        if (cur_connect_info.callback == nullptr) {
            SLOGE("callback is null, will terminate! url:{}", cur_connect_info.listen_url);
            return -1;
        }
    }
    return 0;
}

void MgHttpServer::do_connect_() {

    if (check_connect_info_()) {
        SLOGE("will return connect");
        return;
    }

    struct mg_mgr mgr;
    mg_log_set(MG_LL_INFO);
    mg_mgr_init(&mgr);

    int listen_count = 0;
    for (auto& cur_connect_info : vec_connect_) {
        listen_count++;
        struct mg_connection *connection;
        auto& url = cur_connect_info.listen_url;
        auto& callback = cur_connect_info.callback;
        if ((connection = mg_http_listen(&mgr, url.c_str(), callback, this)) == NULL) {
            std::string msg = fmt::format("cannot listen on {} use http://addr:port or :port, listen count:{}",url.c_str(), listen_count);
            SLOGE(msg);
            throw std::logic_error(msg);
        }
        connection->is_hexdumping = 0;
        SLOGI("start listening on: {}, listen count:{}", url.c_str(), listen_count);
    }

    int poll_count = 0;
    while (!to_stop_ && !SignalHandle::ins().signal_status_SIGINT()) {
        mg_mgr_poll(&mgr, poll_timeout_ms_);
        poll_count++;
        if (poll_count > 100) {
            poll_count = 0;
            printf(">");
            fflush(stdout);
        }
    }
    SLOGI("state value, to_stop_:{}, sigint:{}", to_stop_, SignalHandle::ins().signal_status_SIGINT());
    
    mg_mgr_free(&mgr);
    for (auto& cur_connect_info : vec_connect_) {
        SLOGW("http listen exit, ip:{}", cur_connect_info.listen_url);
    }
}


