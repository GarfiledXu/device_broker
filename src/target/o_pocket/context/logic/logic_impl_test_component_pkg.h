#include "logic_impl_test_component.h"

//./new_service function test_http_server
class Cli11Option_test_http_server : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_http_server";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_http_server");
    };
    virtual int call_funtion() override {
        int ret = test_http_server();
        if (ret) {
            SLOGE("call test_http_server fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};
//test_http_objective_server
//./new_service function test_http_objective_server

class Cli11Option_test_http_objective_server : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_http_objective_server";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_http_objective_server");
    };
    virtual int call_funtion() override {
        int ret = test_http_objective_server();
        if (ret) {
            SLOGE("call test_http_server fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};


//test_threadloop_front
//./new_service function test_threadloop_front
class Cli11Option_test_threadloop_front : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_threadloop_front";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_threadloop_front");
    };
    virtual int call_funtion() override {
        int ret = test_threadloop_front();
        if (ret) {
            SLOGE("call test_threadloop_front fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};

//test_threadloop_back
//./new_service function test_threadloop_back
class Cli11Option_test_threadloop_back : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_threadloop_back";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_threadloop_back");
    };
    virtual int call_funtion() override {
        int ret = test_threadloop_back();
        if (ret) {
            SLOGE("call test_threadloop_back fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};

//./new_service function test_threadloop_back_detach
class Cli11Option_test_threadloop_back_detach : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_threadloop_back_detach";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_threadloop_back_detach");
    };
    virtual int call_funtion() override {
        int ret = test_threadloop_back_detach();
        if (ret) {
            SLOGE("call test_threadloop_back_detach fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};
//./new_service function test_threadloop_back_join
class Cli11Option_test_threadloop_back_join : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_threadloop_back_join";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_threadloop_back_join");
    };
    virtual int call_funtion() override {
        int ret = test_threadloop_back_join();
        if (ret) {
            SLOGE("call test_threadloop_back_join fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};


//test_http_server_with_state_manager
class Cli11Option_test_http_server_with_state_manager : public Cli11OptionBase {
public:
    
    std::string sub_cmd_name = "test_http_server_with_state_manager";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "test_http_server_with_state_manager");
    };
    virtual int call_funtion() override {
        int ret = test_http_server_with_state_manager();
        if (ret) {
            SLOGE("call test_http_server_with_state_manager fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};