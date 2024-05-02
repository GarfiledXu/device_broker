#include "logic_impl_service.h"

int http_service_objective()
{
    //register cfg singleton
    //register threadpool
    //register threadpool monitor
    //launch http service
    TimeInterval<> time_interval{};

    ThreadloopObjectiveFSM::ins().launch_back();

    MgHttpServer mg_http_server{
        {
            {"http://0.0.0.0:12345", http_server_objective_callback}, 
        },
        5000,
        5000
    };
    mg_http_server.launch();

    ObjectiveComponentManager::ins().to_stop_signal();

    ThreadloopObjectiveFSM::ins().to_stop_singal();
    ThreadloopObjectiveFSM::ins().join();

    SLOGW("out http objective server, cost time: [{}] ms", time_interval.get_interval_ms());
    return 0;

}

int http_service_i30()
{

}

int http_service_objective_i30()
{

}

int websocket_service_device_ping()
{

}

