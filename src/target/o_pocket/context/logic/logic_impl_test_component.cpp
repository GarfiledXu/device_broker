#include "logic_impl_test_component.h"

//test pass
int test_http_server()
{
    auto callback1 = [](struct mg_connection* c, int ev, void* ev_data) {
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
    auto callback2 = [](struct mg_connection *c, int ev, void *ev_data) {
        if (ev == MG_EV_HTTP_MSG) {
            SLOGD("enter callback2 message print");
            struct mg_http_message *hm = (mg_http_message*)ev_data, tmp = {0};
            SLOGI("get http message:\n{}", std::string(hm->message.ptr, hm->message.len));
        }
    };
    TimeInterval<> time_interval{};
    MgHttpServer mg_http_server{
        {
            {"http://0.0.0.0:12345", callback1}, 
            {"http://0.0.0.0:54321", callback2}, 
        },
        5000,
        5000
    };
    MgHttpServer mg_http_server2{
        {
            {"http://0.0.0.0:12346", callback1}, 
            {"http://0.0.0.0:64321", callback2}, 
        },
        5000,
        5000
    };
    
    std::thread thread_http_server2 = std::thread([&]() {
        mg_http_server2.launch();
        SLOGW("mg_http_server2 out");
        });
    thread_http_server2.detach();
    
    mg_http_server.launch();
    SLOGW("mg_http_server1 out");
    SLOGW("out test http server, cost time: [{}] ms", time_interval.get_interval_ms());
}

//test objective server 
int test_http_objective_server()
{
    TimeInterval<> time_interval{};
    MgHttpServer mg_http_server{
        {
            {"http://0.0.0.0:12345", http_server_objective_callback}, 
        },
        5000,
        5000
    };
    
    mg_http_server.launch();
    SLOGW("mg_http_server1 out");
    SLOGW("out test http server, cost time: [{}] ms", time_interval.get_interval_ms());
}

int backend_load_http_i30_server()
{

};

int backend_load_http_objective_server()
{

};

int backend_load_http_file_proxy_server()
{

}

//pass
int test_threadloop_front()
{
    Threadlooper_I30_Qnx700 threadlooper{};
    threadlooper.launch_front();
    return 0;
}

//pass
int test_threadloop_back()
{
    Threadlooper_I30_Qnx700 threadlooper{};
    threadlooper.launch_back();
    // threadlooper.join();
    SLOGD("enter sleep 3000 ms");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    SLOGD("out sleep 3000 ms");
    return 0;
}

//pass
int test_threadloop_back_detach()
{
    Threadlooper_I30_Qnx700 threadlooper{};
    threadlooper.launch_back();
    threadlooper.detach();
    SLOGD("enter sleep 3000 ms");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    SLOGD("out sleep 3000 ms");
    return 0;
}

//pass
int test_threadloop_back_join()
{
    Threadlooper_I30_Qnx700 threadlooper{};
    threadlooper.launch_back();
    threadlooper.join();
    return 0;
}

//pass
int test_http_server_with_state_manager()
{
    TimeInterval<> time_interval{};
    MgHttpServer mg_http_server{
        {
            {"http://0.0.0.0:12345", http_server_objective_callback}, 
        },
        5000,
        5000
    };
    // thread looper
    Threadlooper_I30_Qnx700 threadlooper{};
    threadlooper.launch_back();
    
    mg_http_server.launch();
    SLOGW("mg_http_server1 out");
    threadlooper.to_stop();
    threadlooper.join();
    SLOGW("out test http server, cost time: [{}] ms", time_interval.get_interval_ms());
}