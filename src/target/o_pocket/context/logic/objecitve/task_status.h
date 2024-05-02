#ifndef GF_TASK_STATUS_H
#define GF_TASK_STATUS_H
#include "my-internal.h"
#include "enum-convert-macro.hpp"
#include "bit-operator.hpp"

GF_NAMESPACE_START(main_service)
enum STATE_DEVICE {
        STATE_DEVICE_INVALID = 0,
        FREE = 1 << 0,
        BUSY = 1 << 1,
        UPDATINTG = 1 << 2,
        UPDATED = 1 << 3,
        UPDATE_SUCCESS = 1 << 4,
        UPDATE_FAIL = 1 << 5,
        REBOOTING = 1 << 6,
        REBOOT_SUCCESS = 1 << 7,

        FILE_PULL = 1 << 8,
        FILE_PULL_FAIL = 1 << 9,
        FILE_PULL_SUCCESS = 1 << 10,
        FILE_CLEAR = 1 << 11,
        FILE_CLEAR_FAIL = 1 << 12,
        FILE_CLEAR_SUCCESS = 1 << 13

        // LICENSE_CHECK_FAIL = 1 << 8,
        // LICENSE_NO_FILE = 1 << 9,
        // LIB_NEAT_FAIL = 1 << 10
        // REBOOTING = 1 << 7,
        // REBOOT_SUCCESS = 1 << 6
};
enum STATE_TASK {
        STATE_TASK_INVALID = 0,
        DIVORCED = 1 << 0,
        ACCEPTED = 1 << 1,
        RUNNING = 1 << 2,
        RETURN_SUCCESS = 1 << 3,
        RETURN_ERROR = 1 << 4,
        UPLOADING = 1 << 5,
        UPLOADED = 1 << 6,
        UPLOAD_SUCCESS = 1 << 7,
        UPLOAD_FAIL = 1 << 8,
        CALL_FAILED = 1 << 9,
        LICENSE_CHECK_FAIL = 1 << 10,
        LICENSE_NO_FILE = 1 << 11,
        RABBITMQ_SUCCESS = 1 << 12,
        RABBITMQ_FAIL = 1 << 13,
        RABBITMQ_ING = 1 << 14,
        RABBITMQ_END = 1 << 15
};
STRING_ENUM_CONVERT_GENERATOR_CURR_NAMESPACE(STATE_TASK,
    STATE_TASK_INVALID,
    DIVORCED ,
    ACCEPTED ,
    RUNNING ,
    RABBITMQ_SUCCESS ,
    RABBITMQ_FAIL ,
    RABBITMQ_ING ,
    RABBITMQ_END 
);
STRING_ENUM_CONVERT_GENERATOR_CURR_NAMESPACE(STATE_DEVICE,
    STATE_DEVICE_INVALID,
    FREE,
    BUSY,
    UPDATINTG,
    UPDATED,
    UPDATE_SUCCESS,
    UPDATE_FAIL,
    REBOOTING,
    REBOOT_SUCCESS,

    FILE_PULL_FAIL,
    FILE_PULL,
        FILE_PULL_SUCCESS,
        FILE_CLEAR,
        FILE_CLEAR_FAIL,
        FILE_CLEAR_SUCCESS
);

enum TASK_TYPE {
    TASK_TYPE_UPDATE,
    TASK_TYPE_RUNING,
    TASK_TYPE_SUB_DOWN,
    TASK_TYPE_SUB_RUNNING,
    TASK_TYPE_UPLOAD
};

#define BIT_MATCH_ADD_TO_STRING(target_str, state, item) \
if (BIT_MATCH_COMBINE_SUBSET(state, item)) { \
        target_str += (enum_to_string(item)+" "); }

class TaskStatus {
public:
    GF_CLASS_DELETE_COPY(TaskStatus);
    TaskStatus(const size_t initial_task_state, const size_t initial_device_state): device_state_(initial_device_state), task_state_(initial_task_state){};
    virtual ~TaskStatus(){};

    size_t get_task_state() {
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        return task_state_; 
    }
    size_t  get_device_state(){ 
        std::unique_lock<std::mutex> ul(device_state_mutex_);
        return device_state_; 
    }

    /**
     *@brief Get the task state str object, 将枚举值转字符串拼接在一起，在tmanager中已有实现
     * @return const char* 
     */
    std::string get_task_state_str() {
        std::unique_lock<std::mutex> ul(task_state_mutex_); 
        std::string ret;
        ret = std::to_string(task_state_) + " ";
        // BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::STATE_TASK_INVALID);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::DIVORCED);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::ACCEPTED);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::RUNNING);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::RABBITMQ_SUCCESS);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::RABBITMQ_FAIL);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::RABBITMQ_ING);
        BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::RABBITMQ_END);
        // BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::UPLOADING);
        // BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::CALL_FAILED);
        // BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::LICENSE_CHECK_FAIL);
        // BIT_MATCH_ADD_TO_STRING(ret, task_state_, STATE_TASK::LICENSE_NO_FILE);
        return ret;
    }
    std::string get_device_state_str() { 
        std::unique_lock<std::mutex> ul(device_state_mutex_);
        std::string ret;
        ret = std::to_string(device_state_) + " ";
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FREE);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::BUSY);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::UPDATINTG);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::UPDATED);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::UPDATE_SUCCESS);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::UPDATE_FAIL);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::REBOOTING);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::REBOOT_SUCCESS);

        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_PULL);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_PULL_FAIL);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_PULL_SUCCESS);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_CLEAR);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_CLEAR_FAIL);
        BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::FILE_CLEAR_SUCCESS);
    
        // BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::LICENSE_CHECK_FAIL);
        // BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::LICENSE_NO_FILE);
        // BIT_MATCH_ADD_TO_STRING(ret, device_state_, STATE_DEVICE::LIB_NEAT_FAIL);
        return ret;
    }
    /**
     *@brief 使用 | 添加add task state, 返回this引用，翻遍链式调用
     */
    TaskStatus& add_task_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        task_state_ |=  invalue;
        return *this; 
    }

    TaskStatus& add_device_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(device_state_mutex_); 
        device_state_ |= invalue;
        return *this; 
    }
    /**
     *@brief 清空未state值为invalid，并返回this引用，方便链式调用
     */
    TaskStatus& reset_task_state() { 
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        task_state_ = STATE_TASK::STATE_TASK_INVALID;
        return *this; 
    }
    TaskStatus& reset_device_state() {
        std::unique_lock<std::mutex> ul(device_state_mutex_); 
        device_state_ = STATE_DEVICE::STATE_DEVICE_INVALID;
        return *this; 
    }
    /**
     *@brief 使用参数值替换内含值，返回this引用
     * @return TaskStatus& 
     */
    TaskStatus& replace_task_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        task_state_ = invalue;
        return *this; 
    }
    TaskStatus& replace_device_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(device_state_mutex_); 
        device_state_ = invalue;
        return *this; 
    }
    /**
     *@brief 判断是否包含某些值，tmanager已有实现
     * @param invalue 
     * @return true 
     * @return false 
     */
    bool is_contain_task_state(const size_t invalue) { 
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        return BIT_MATCH_COMBINE_SUBSET(task_state_, invalue); 
    }
    bool is_contain_device_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(device_state_mutex_); 
        return BIT_MATCH_COMBINE_SUBSET(device_state_, invalue); 
    }
    /**
     *@brief 判断是否完全相等
     * @param invalue 
     * @return true 
     * @return false 
     */
    bool is_equal_task_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        return task_state_ == invalue; 
    }
    bool is_equal_device_state(const size_t invalue) {
        std::unique_lock<std::mutex> ul(device_state_mutex_); 
        return device_state_ == invalue; 
    }
    bool is_equal_task_state(TaskStatus intask_status){
        std::unique_lock<std::mutex> ul(task_state_mutex_);
        return task_state_ == intask_status.get_task_state(); 
    }
    bool is_equal_device_state(TaskStatus intask_status){
        std::unique_lock<std::mutex> ul(device_state_mutex_);
        return device_state_ == intask_status.get_device_state(); 
    }


    /**
     *@brief operator重载实现，优先实现顺序：==,  先不实现
     */

    
private:
    size_t task_state_, device_state_;
    std::mutex task_state_mutex_, device_state_mutex_;
    /**
     *@brief 任务状态值有效检查，一期先不实现，直接返回true
     * @param state 
     * @return true 
     * @return false 
     */
    bool task_state_check(const size_t state) { return true; };
    bool device_state_check(const size_t state) { return true; };

};
GF_NAMESPACE_END(main_service)

extern main_service::TaskStatus g_task_state;
#endif