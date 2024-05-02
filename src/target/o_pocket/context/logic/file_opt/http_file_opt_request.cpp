#include "http_file_opt_request.h"

TaskSuitBase::TaskReturn file_operation_file_pull(TaskFileOperation_FilePull file_pull_info)
{
    int ret = 0;

    bool is_protocol_correct = (file_pull_info.protocol == "smb");
    bool is_src_type_correct = (file_pull_info.src_type == "core_file") || (file_pull_info.src_type == "log_file");
    bool is_opt_type_correct = (file_pull_info.opt_type == "copy");

    if (!is_protocol_correct || !is_src_type_correct || !is_opt_type_correct) {

        SLOGE("check file pull info fail!");

        ret = -1;
        return TaskSuitBase::TaskReturn{ret, "check file pull info fail", TASK_FILE_OPT_FILE_PULL};
    }

    std::string dst_local_dir_path = "";
    std::string suffix = "";

    if (file_pull_info.src_type == "core_file") {
        dst_local_dir_path = "/var/log";
        suffix = ".core";
    }
    else if(file_pull_info.src_type == "log_file") {
        dst_local_dir_path = "/var/i30_objective/objective/log";
        suffix = ".log";
    }

    ret = smb_remote_upload_file_by_suffix(file_pull_info.dst_url, dst_local_dir_path, suffix
        , file_pull_info.smb_usr, file_pull_info.smb_passwd);
    if (ret) {

        SLOGE("smb_remote_upload_file_by_suffix fail, ret:{}", ret);

        ret = -2;
        return TaskSuitBase::TaskReturn{ret, "check file pull info fail", TASK_FILE_OPT_FILE_PULL};
    }
    

    ret = 0;
    return TaskSuitBase::TaskReturn(ret, "file pull opt success", TASK_FILE_OPT_FILE_PULL);
}

TaskSuitBase::TaskReturn file_operation_file_clear(TaskFileOperation_FileClear file_clear_info)
{
    int ret = 0;

    bool is_src_type_correct = (file_clear_info.src_type == "core_file") || (file_clear_info.src_type == "log_file");
    if (!is_src_type_correct) {

        SLOGE("check file_clear_info fail!");

        ret = -1;
        return TaskSuitBase::TaskReturn{ret, "check file_clear_info fail", TASK_FILE_OPT_FILE_CLEAR};
    }

    std::string dst_local_dir_path = "";
    std::string suffix = "";

    if (file_clear_info.src_type == "core_file") {
        dst_local_dir_path = "/var/log";
        suffix = ".core";
    }

    std::vector<std::string> clear_file_list;
    ret = find_file_list_by_suffix(dst_local_dir_path, clear_file_list, suffix);
    if (ret) {
        SLOGE("find_file_list_by_suffix fail! ret:{}", ret);
        ret = -2;
        return TaskSuitBase::TaskReturn{ret, "find_file_list_by_suffix fail", TASK_FILE_OPT_FILE_CLEAR};
    }

    ret = clear_file(clear_file_list);
    if (ret) {
        SLOGE("clear file fail! ret:{}", ret);
        ret = -3;
        return TaskSuitBase::TaskReturn{ret, "clear_file fail", TASK_FILE_OPT_FILE_CLEAR};
    }

    return TaskSuitBase::TaskReturn();
}
