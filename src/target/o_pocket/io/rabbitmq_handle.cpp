#include "rabbitmq_handle.h"
#include "log.h" // new zjx9083
// int32_t LOG_LEVEL_MASK = EROR | VEBO | PRINT | INFO | DBUG | COLOR | EXTR;

RabbitMQHandler::RabbitMQHandler(string req){   
    state_ = 0;
    json j;
    try {
        j = json::parse(req);
        SLOGI("RabbitMQHandler vtor parse req success:{}", req.c_str());
    } catch (json::parse_error& e) {
        state_ = -1;
        SLOGE("error! RabbitMQHandler vtor parse req, content:{}", e.what());
    }

    PARSE_JSON_VALUE_STR(j, hostname, "hostname", state_, "RabbitMQHandler vtor parse req hostname success:%s\n", "error! RabbitMQHandler vtor parse req hostname not exist\n");
    PARSE_JSON_VALUE_INT(j, port, "port", state_, "RabbitMQHandler vtor parse req port success:%d\n", "error! RabbitMQHandler vtor parse req port not exist\n");
    PARSE_JSON_VALUE_STR(j, username, "username", state_, "RabbitMQHandler vtor parse req username success:%s\n", "error! RabbitMQHandler vtor parse req username not exist\n");
    PARSE_JSON_VALUE_STR(j, password, "password", state_, "RabbitMQHandler vtor parse req password success:%s\n", "error! RabbitMQHandler vtor parse req password not exist\n");
    PARSE_JSON_VALUE_STR(j, exchange, "exchange", state_, "RabbitMQHandler vtor parse req exchange success:%s\n", "error! RabbitMQHandler vtor parse req exchange not exist\n");
    PARSE_JSON_VALUE_STR(j, vhost, "vhost", state_, "RabbitMQHandler vtor parse req vhost success:%s\n", "error! RabbitMQHandler vtor parse req vhost not exist\n");
    PARSE_JSON_VALUE_STR(j, receiveRoutingkey, "receive_routing_key", state_, "RabbitMQHandler vtor parse req receive_routing_key success:%s\n", "error! RabbitMQHandler vtor parse req receive_routing_key not exist\n");
    PARSE_JSON_VALUE_STR(j, receiveQueueName, "receive_queue_name", state_, "RabbitMQHandler vtor parse req receive_queue_name success:%s\n", "error! RabbitMQHandler vtor parse req receive_queue_name not exist\n");
    PARSE_JSON_VALUE_STR(j, sendRoutingKey, "send_routing_key", state_, "RabbitMQHandler vtor parse req send_routing_key success:%s\n", "error! RabbitMQHandler vtor parse req send_routing_key not exist\n");
    PARSE_JSON_VALUE_STR(j, sendQueueName, "send_queue_name", state_, "RabbitMQHandler vtor parse req send_queue_name success:%s\n", "error! RabbitMQHandler vtor parse req send_queue_name not exist\n");

    state_ = connection();
}

int RabbitMQHandler::connection(){
    SLOGI("establish sendConn");
    sendConn = amqp_new_connection();
    if(!sendConn && sendConn==0){
        SLOGE("amqp_new_connection() sendConn");
        return -1;
    }
    SLOGI("establish receiveConn");
    receiveConn = amqp_new_connection();
    if(!receiveConn && receiveConn==0){
        SLOGE("amqp_new_connection() receiveConn");
        return -2;
    }

    amqp_socket_t* sendSocket = amqp_tcp_socket_new(sendConn);
    SLOGI("Creating TCP sendSocket");
    if (!sendSocket) {
        SLOGE("Creating TCP sendSocket failed");
        return -3;
    }
    amqp_socket_t* receiveSocket = amqp_tcp_socket_new(receiveConn);
    SLOGI("Creating TCP receiveSocket");
    if (!receiveSocket) {
        SLOGE("Creating TCP receiveSocket failed");
        return -4;
    }

    SLOGI("Opening TCP sendSocket");
    int status = amqp_socket_open(sendSocket, hostname.c_str(), port);
    if (status) {
        SLOGE("Opening TCP sendSocket failed");
        return -5;
    }
    SLOGI("Opening TCP receiveSocket");
    status = amqp_socket_open(receiveSocket, hostname.c_str(), port);
    if (status) {
        SLOGE("Opening TCP receiveSocket failed");
        return -6;
    }

    SLOGI("Login remote rabbitmq");
    amqp_rpc_reply_t login_reply1 = amqp_login(sendConn, vhost.c_str(), 0, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, username.c_str(), password.c_str());
    amqp_rpc_reply_t login_reply2 = amqp_login(receiveConn, vhost.c_str(), 0, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, username.c_str(), password.c_str());
    if (login_reply1.reply_type != AMQP_RESPONSE_NORMAL || login_reply2.reply_type != AMQP_RESPONSE_NORMAL) {
        SLOGE("Login failed");
        return -7;
    }

    SLOGI("Opening channel");
    amqp_channel_open(sendConn, 2);
    amqp_channel_open(receiveConn, 2);

    amqp_rpc_reply_t channel_reply1 = amqp_get_rpc_reply(sendConn);
    amqp_rpc_reply_t channel_reply2 = amqp_get_rpc_reply(receiveConn);
    if (channel_reply1.reply_type != AMQP_RESPONSE_NORMAL || channel_reply2.reply_type != AMQP_RESPONSE_NORMAL) {
        SLOGE("Opening channel failed");
        return -8;
    }

    SLOGI("Queue get");
    amqp_queue_bind_ok_t * ret1 = amqp_queue_bind(sendConn, 2, amqp_cstring_bytes(receiveQueueName.c_str()), amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(receiveRoutingkey.c_str()), amqp_empty_table);
    amqp_queue_bind_ok_t * ret2 = amqp_queue_bind(receiveConn, 2, amqp_cstring_bytes(sendQueueName.c_str()), amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(sendRoutingKey.c_str()), amqp_empty_table);
    if (!ret1 || !ret2) {
        SLOGE("Queue get failed");
        return -9;
    }
    return 0;
}

int RabbitMQHandler::sendMessage(const std::string& message) {
    SLOGD("enter mylock mutex");
    std::lock_guard<std::mutex> mylock(mutex_);
    SLOGI("Send Message to remote rabbitmq, Message content: {}", message.c_str());
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("application/test");
    // props.content_encoding = amqp_cstring_bytes("Base64");
    props.delivery_mode = 2;
    // std::string encoded_message = base64_encode(message.c_str(), message.length());
    // SLOGI("Message base64: %s\n", encoded_message.c_str());
    amqp_bytes_t message_bytes = amqp_cstring_bytes(message.c_str());

    int ret = amqp_basic_publish(sendConn, 2, amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(sendRoutingKey.c_str()), 0, 0, &props, message_bytes);
    if(ret){
        SLOGE("Send message to remote rabbitmq failed ret:{}", ret);
        return ret;
    }
    SLOGI("Send message to remote rabbitmq success");
    SLOGD("out mylock mutex");
    return 0;
}

// std::string RabbitMQHandler::receiveMessage(){
//     SLOGI("Starting consumer\n");
//     amqp_basic_consume(receiveConn, 2, amqp_cstring_bytes(receiveQueueName.c_str()), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
//     amqp_rpc_reply_t consume_reply = amqp_get_rpc_reply(receiveConn);
//     if (consume_reply.reply_type != AMQP_RESPONSE_NORMAL) {
//         LOG_ERROR("Starting consumer failed\n");
//         return "";
//     }
//     SLOGI("Start receive message from remote rabbitmq\n");
//     amqp_envelope_t envelope;
//     amqp_maybe_release_buffers(receiveConn);
//     amqp_rpc_reply_t ret = amqp_consume_message(receiveConn, &envelope, NULL, 0);
//     if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
//         SLOGI("Remote rabbitmq not have message\n");
//         return "";
//     }
//     if(strcmp((char*)envelope.message.body.bytes,"")==0){
//         SLOGI("Remote rabbitmq message is empty\n");
//         amqp_basic_ack(receiveConn, 2, envelope.delivery_tag, 0);
//         amqp_destroy_envelope(&envelope); 
//         return "";
//     }
//     SLOGI("receive message from remote rabbitmq: %s\n", (char*)envelope.message.body.bytes);
//     std::string res = (char*)envelope.message.body.bytes;
//     amqp_basic_ack(receiveConn, 2, envelope.delivery_tag, 0);
//     amqp_destroy_envelope(&envelope);
//     amqp_basic_cancel(receiveConn, 2, amqp_empty_bytes); 
//     return res;
// }

int RabbitMQHandler::receiveMessage(std::string& task){
    SLOGD("enter mylock mutex");
    SLOGD("\n");
    std::lock_guard<std::mutex> mylock(mutex_);
    SLOGD("\n");
    #if 1
    // SLOGI("Start receive message from remote rabbitmq\n");
    amqp_maybe_release_buffers(receiveConn);
    SLOGD("\n");
    amqp_rpc_reply_t res_get_ok = amqp_basic_get(receiveConn, 2, amqp_cstring_bytes(receiveQueueName.c_str()), 1);
        SLOGD("\n");
    if (AMQP_BASIC_GET_EMPTY_METHOD == res_get_ok.reply.id) {
        SLOGD("\n");
        // SLOGI("Remote rabbitmq message is empty\n");
        sleep(3);
        SLOGD("\n");
        return -1;
    }else if(AMQP_RESPONSE_NORMAL != res_get_ok.reply_type){
        
    SLOGD("\n");
        SLOGE("Failed to get message from remote rabbitmq, error code {}", static_cast<int>(res_get_ok.reply_type));
        return -2;
    }
        SLOGD("\n");
    amqp_message_t message;
        SLOGD("\n");
    amqp_maybe_release_buffers(receiveConn);
        SLOGD("\n");
    amqp_rpc_reply_t res = amqp_read_message(receiveConn, 2, &message, 0);
    // amqp_rpc_reply_t res = amqp_simple_wait_frame_noblock(receiveConn, &message);
    // if (result < 0) {
    //     return -9;
    //     }
        SLOGD("\n");
    if ( AMQP_RESPONSE_NORMAL != res.reply_type) {
            SLOGD("\n");
        SLOGE("Failed to read message from remote rabbitmq, error code {}", static_cast<int>(res.reply_type));
        return -3;
    }
        SLOGD("\n");
    task = std::string((char*)message.body.bytes, message.body.len);
    SLOGI("receive message from remote rabbitmq:{}", task.c_str());
        SLOGD("\n");
    // amqp_basic_ack(receiveConn, 2, ((amqp_basic_ack_t *) res.reply.decoded)->delivery_tag, 0);
    amqp_destroy_message(&message);
    #endif
    
    SLOGD("out mylock mutex");
    return 0;
}

void RabbitMQHandler::disconnection(){
    amqp_channel_close(sendConn, 2, AMQP_REPLY_SUCCESS);
    amqp_connection_close(sendConn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(sendConn);
    
    amqp_channel_close(receiveConn, 2, AMQP_REPLY_SUCCESS);
    amqp_connection_close(receiveConn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(receiveConn);
}

RabbitMQHandler::~RabbitMQHandler(){
    disconnection();
}