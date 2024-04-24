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

int test_http_server();
int test_threadloop_back();
int test_threadloop_back_detach();
int test_threadloop_back_join();
int test_threadloop_front();
int  test_http_server_with_state_manager();
int test_http_objective_server();