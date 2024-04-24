#pragma once
#include "logic_impl_service.h"


//./new_service service http_service_objective 
class Cli11Option_http_service_objective : public Cli11OptionBase
{
public:
    std::string sub_cmd_name = "http_service_objective";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "http_service_objective");
    };
    virtual int call_funtion() override {
        int ret = http_service_objective();
        if (ret) {
            SLOGE("http_service_objective fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};

class Cli11Option_http_service_i30 : public Cli11OptionBase
{
public:
    std::string sub_cmd_name = "http_service_i30";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "http_service_i30");
    };
    virtual int call_funtion() override {
        int ret = http_service_i30();
        if (ret) {
            SLOGE("http_service_i30 fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};

class Cli11Option_http_service_objective_i30 : public Cli11OptionBase
{
public:
    std::string sub_cmd_name = "http_service_objective_i30";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "http_service_objective_i30");
    };
    virtual int call_funtion() override {
        int ret = http_service_objective_i30();
        if (ret) {
            SLOGE("http_service_objective_i30 fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};

class Cli11Option_websocket_service_device_ping : public Cli11OptionBase
{
public:
    std::string sub_cmd_name = "websocket_service_device_ping";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "websocket_service_device_ping");
    };
    virtual int call_funtion() override {
        int ret = websocket_service_device_ping();
        if (ret) {
            SLOGE("websocket_service_device_ping fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};