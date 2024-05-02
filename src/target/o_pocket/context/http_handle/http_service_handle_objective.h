#pragma once
#include "http_server.h"
#include "http_handler.h"
#include "state_suit.h"
#include "log.h"
#include "json.hpp"
using json = nlohmann::json;

using http_handle_prototype = std::function<void(const RequestInfo&, ResponseInfo&)>;
struct MatchItem {
    std::string uri;
    std::string method;
    http_handle_prototype handle;
    MatchItem(std::string in_uri, std::string in_method, http_handle_prototype in_handle)
        : uri(in_uri), method(in_method), handle(std::move(in_handle)) {};
};

void http_server_objective_callback(struct mg_connection* c, int ev, void* ev_data);

static void handle_status(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_update(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_terminate(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_run_objective(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_log(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_test(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_file_pull(const RequestInfo& request_info, ResponseInfo& return_reponse);
static void handle_file_clear(const RequestInfo& request_info, ResponseInfo& return_reponse);

#define MAKE_STR_UNI_PTR(...) std::unique_ptr<std::string>(new std::string(__VA_ARGS__ ))
