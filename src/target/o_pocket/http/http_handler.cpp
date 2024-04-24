//xjf add
#include "http_handler.h"
#include "arpa/inet.h"
#include "log.h"

//static
void MgHttpServerHandler::output_uniform_callback(mg_connection* c, int ev, void* ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        //receive variable
        static RequestInfo tmp_request_info;
        static ResponseInfo tmp_reponse_info;

        static auto get_ip_str = [](struct mg_addr& addr) {
            char buf[100];
            mg_snprintf(buf, sizeof(buf), "%M", mg_print_ip, &addr);  
            return std::unique_ptr<std::string>(new std::string(buf));
        };
        static auto get_port_str = [](struct mg_addr& addr) {
            char buf[100];
            return std::unique_ptr<std::string>(new std::string(std::to_string(mg_ntohs(addr.port))));
        };
        static auto get_port_value = [](struct mg_addr& addr) {
            char buf[100];
            return mg_ntohs(addr.port);
        };
        static auto get_ip_port_str = [](struct mg_addr& addr) {
            char buf[100];
            mg_snprintf(buf, sizeof(buf), "%M", mg_print_ip_port, &addr);  
            return std::unique_ptr<std::string>(new std::string(buf));
        };
        
        //assign before
        // SLOGW("rem ip:{}, port:{}", *get_ip_str(c->rem), *get_port_str(c->rem));
        // SLOGW("rem ip_port:{}", *get_ip_port_str(c->rem));
        // SLOGW("loc ip:{}, port:{}", *get_ip_str(c->loc), *get_port_str(c->loc));
        // SLOGW("loc ip_port:{}", *get_ip_port_str(c->loc));

        // strcpy(tmp_request_info.sender_ip, c->loc.ip);
        // tmp_request_info.sender_ip = c->loc.ip;
        tmp_request_info.hm = hm;
        memcpy(tmp_request_info.sender_ip, reinterpret_cast<char*>(c->rem.ip), sizeof(c->rem.ip));
        tmp_request_info.sender_port = get_port_value(c->rem);
        memcpy(tmp_request_info.listener_ip, reinterpret_cast<char*>(c->loc.ip), sizeof(c->loc.ip));
        tmp_request_info.listener_port = get_port_value(c->loc);

        tmp_request_info.sender_ip_port_str = get_ip_port_str(c->rem);
        tmp_request_info.sender_port_str = get_port_str(c->rem);
        tmp_request_info.sender_ip_str = get_ip_str(c->rem);

        tmp_request_info.listener_ip_port_str = get_ip_port_str(c->loc);
        tmp_request_info.listener_port_str = get_port_str(c->loc);
        tmp_request_info.listener_ip_str = get_ip_str(c->loc);

        tmp_request_info.method = std::string(hm->method.ptr, hm->method.len);
        tmp_request_info.uri = std::string(hm->uri.ptr, hm->uri.len); 
        tmp_request_info.body = std::string(hm->body.ptr, hm->body.len);  

        //clean
        tmp_reponse_info.errcode = 0;
        tmp_reponse_info.header = "";
        tmp_reponse_info.body = "";

        //printf assign after
        request_response_info_print(tmp_request_info, tmp_reponse_info);

        //filter and call router
        auto& cur_list = MgHttpServerHandler::ins().router_list();
        for (auto& cur_ptr : cur_list) {
            if (!cur_ptr->enable_) {
                continue;
            }
            char buf[100] = { 0 };
            int ret = cur_ptr->http_msg_accept(tmp_request_info, tmp_reponse_info);
            //返回0，则处理
            if (!ret) {
                mg_http_reply(c, tmp_reponse_info.errcode, tmp_reponse_info.header.c_str(), tmp_reponse_info.body.c_str());
                break;
            }
        }
    }
}

void MgHttpServerHandler::request_response_info_print(const RequestInfo& tmp_request_info, const ResponseInfo& tmp_response_info) {
SLOGD("printinfo,\n"
        "sender  ip_port_str:{}, port_str:{}, ip_str:{}, ip:{}, port:{}\n"
        "listener  ip_port_str:{}, port_str:{}, ip_str:{}, ip:{}, port:{}\n"
        "method:{}, uri:{}, body:\n{}",
        *tmp_request_info.sender_ip_port_str, *tmp_request_info.sender_port_str, *tmp_request_info.sender_ip_str, fmt::join(tmp_request_info.sender_ip, ".") , tmp_request_info.sender_port, 
        *tmp_request_info.listener_ip_port_str, *tmp_request_info.listener_port_str, *tmp_request_info.listener_ip_str, fmt::join(tmp_request_info.listener_ip, ".") , tmp_request_info.listener_port,
        tmp_request_info.method, tmp_request_info.uri, tmp_request_info.body);
}


bool MgHttpServerHandler::router_list_check() {
    //check enable
    //if count is 0, mean will no response
    int enable_counter = 0;
    for (auto& cur_router : router_list_) {
        if (cur_router->enable_) {
            enable_counter++;
        }
    }
    if (enable_counter == 0) {
        return false;
    }
    return true;
}

//static
std::string MgHttpServerHandler::reponse_header_splice(std::list<ResponseHeader> input_header_list) {
    std::string header_str;
    for (const auto& header : input_header_list) {
        header_str += header.key + ": " + header.value + "\r\n";
    }
    return header_str;
}

std::list<Router*>& MgHttpServerHandler::router_list() {
    return router_list_;
}
