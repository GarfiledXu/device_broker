#pragma once
//help macro
#define MG_GET_INFO_REF(define_request_var, define_response_var) \
auto& define_request_var = in_request_info; auto& define_response_var = out_reponse_info;


#define MG_FILTER_INCLUDE_STR(target, target_str) \
if((in_request_info.target) != std::string(target_str)){return -1;}

#define MG_FILTER_EXCLUDE_STR(target, target_str) \
if((in_request_info.target) == std::string(target_str)){return -1;}

#define MG_FILTER_INCLUDE_URI(uri_str) \
MG_FILTER_INCLUDE_STR(uri, uri_str)
#define MG_FILTER_EXCLUDE_URI(uri_str) \
MG_FILTER_EXCLUDE_STR(uri, uri_str)

#define MG_FILTER_INCLUDE_METHOD(method_str) \
MG_FILTER_INCLUDE_STR(method, method_str)
#define MG_FILTER_EXCLUDE_METHOD(method_str) \
MG_FILTER_EXCLUDE_STR(method, method_str)

#define MG_FILTER_INCLUDE_BODY(body_str) \
MG_FILTER_INCLUDE_STR(body, body_str)
#define MG_FILTER_EXCLUDE_BODY(_str) \
MG_FILTER_EXCLUDE_STR(body, body_str)

#define MG_FILTER_INCLUDE_SENDER_IP(_str) \
MG_FILTER_INCLUDE_STR(sender_ip_str, _str)
#define MG_FILTER_EXCLUDE_SENDER_IP(_str) \
MG_FILTER_EXCLUDE_STR(sender_ip_str, _str)

#define MG_FILTER_INCLUDE_SENDER_PORT(_str) \
MG_FILTER_INCLUDE_STR(sender_port_str, _str)
#define MG_FILTER_EXCLUDE_SENDER_PORT(_str) \
MG_FILTER_EXCLUDE_STR(sender_port_str, _str)

#define MG_FILTER_INCLUDE_SENDER_IP_PORT(_str) \
MG_FILTER_INCLUDE_STR(sender_ip_port_str, _str)
#define MG_FILTER_EXCLUDE_SENDER_IP_PORT(_str) \
MG_FILTER_EXCLUDE_STR(sender_ip_port_str, _str)

#define MG_FILTER_INCLUDE_LISTENER_IP(_str) \
MG_FILTER_INCLUDE_STR(listener_ip_str, _str)
#define MG_FILTER_EXCLUDE_LISTENER_IP(_str) \
MG_FILTER_EXCLUDE_STR(listener_ip_str, _str)

#define MG_FILTER_INCLUDE_LISTENER_PORT(_str) \
MG_FILTER_INCLUDE_STR(listener_port_str, _str)
#define MG_FILTER_EXCLUDE_LISTENER_PORT(_str) \
MG_FILTER_EXCLUDE_STR(listener_port_str, _str)

#define MG_FILTER_INCLUDE_LISTENER_IP_PORT(_str) \
MG_FILTER_INCLUDE_STR(listener_ip_port_str, _str)
#define MG_FILTER_EXCLUDE_LISTENER_IP_PORT(_str) \
MG_FILTER_EXCLUDE_STR(listener_ip_port_str, _str)

#define MG_GET_ROUTER_NAME()  name?*name:""
#define MG_GET_ROUTER_PRIORITY()  register_priority

/**
 *@brief
using
IMPL_HTTP_ROUTER(name, enable){
}

 */
//关于使用静态注册
//gtest中的静态注册 , 实例化的什么类型? 添加到什么全局容器? 被实例化的对象注册后的处理? 整个流程关联了哪些类型?
//question: 为什么在testinfo的构造中传入  new了一个用于构造继承test的工程对象，为什么不直接new test对象？   testinfo的目的是在前期(静态注册初始化) 保存好test的相关信息，以及test的构造方法(工厂)，用于在运行时才实例化
//所以gtest中，注册的是托管目标对象的对象，不是直接在静态初始化实例化目标静态对象