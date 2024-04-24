#pragma once

#include <mutex>
#include <string>

#include "log.h"

#include "miniz_impl.inl"
#include "filesystem_impl.inl"
#include "cli11_base.h"
#include "time_interval.inl"

#include "samba_transfer.h"

#include "http_server.h"
#include "http_handler.h"
#include "http_service_handle_objective.h"

#include "threadloop_base.h"
#include "threadloop_i30_qnx700.h"

int http_service_objective();

int http_service_i30();

int http_service_objective_i30();

int websocket_service_device_ping();

class ObjectiveComponentManager {
public:
    ~ObjectiveComponentManager() = default;
    ObjectiveComponentManager& ins() {
        static ObjectiveComponentManager static_ins;
        return static_ins;
    }

    int load();
    int unload();

private:
    ObjectiveComponentManager() = default;
    //threadpool
    //samba
    //rabbitmq
};