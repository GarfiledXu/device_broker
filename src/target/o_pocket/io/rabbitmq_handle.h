#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "component-all.hpp"
#include "log.h" // new zjx9083

using namespace std;

class RabbitMQHandler{ 
#define PARSE_JSON_VALUE_STR(j, var, key, state_, log_success, log_error) \
    if (j.contains(key)) { \
        var = get_json_value<std::string>(j, key); \
        if(var[0]=='\"') var = var.substr(1, var.length() - 2);\
        SLOGI("{}{}",log_success, var.c_str()); \
    } else { \
        state_ = -1; \
        SLOGE("{}",log_error); \
    }
#define PARSE_JSON_VALUE_INT(j, var, key, state_, log_success, log_error) \
    if (j.contains(key)) { \
        var = get_json_value<int>(j, key); \
        SLOGI("{}{}",log_success, var); \
    } else { \
        state_ = -1; \
        SLOGE("{}",log_error); \
    }

public:
    RabbitMQHandler(string);
    // connect remote rabbitmq
    int connection() ;
    // send message to remote rabbitmq
    int sendMessage(const std::string&) ;
    // receive single message from remote rabbitmq
    int receiveMessage(std::string &);
    // disconnection remote rabbitmq
    void disconnection();
    ~RabbitMQHandler();
    int state(){return state_;}
private:
    std::string hostname;
    int port;
    std::string username;
    std::string password;
    std::string exchange;
    std::string vhost;

    std::string receiveRoutingkey;
    std::string receiveQueueName;

    std::string sendRoutingKey;
    std::string sendQueueName;

    std::mutex mutex_;

private:
    amqp_connection_state_t receiveConn;
    amqp_connection_state_t sendConn;
    int state_;
};

#endif