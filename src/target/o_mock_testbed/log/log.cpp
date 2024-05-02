#include "log.h"

NAMESPACE_BEGIN(gf)
GF_INLINE void log::logger_cfg() {
    printf("call derived! logger cfg\n");
    std::string root_dir;
    std::string sub_dirname;
    std::string basename;
    std::string ext;
    //  i30 
    // objective
    std::string predefine_dir = "./log";
    // regi_console_and_gf_sink_to_logger_(INBUILT_LOG_NAME, gen_default_gf_sink_({predefine_dir, "common", "log", ".txt"}, 1024*512*1, 100), gen_default_console_sink_());
    regi_console_sink_to_to_logger_(INBUILT_LOG_NAME, gen_default_console_sink_());
    
    // regi_gf_sink_to_logger_(REC_LISTENER, gen_default_gf_sink_({predefine_dir, "record", "http_listener", ".txt"},  1024*512*1, 100));
    // regi_gf_sink_to_logger_(REC_SYSTEM_CALL, gen_default_gf_sink_({predefine_dir,"record","system_call",".txt"},1024*512*1,100));
    // regi_gf_sink_to_logger_(REC_REQUEST, gen_default_gf_sink_({predefine_dir,"record","http_request",".txt"},1024*512*1,100));
    // regi_gf_sink_to_logger_(REC_MQ_MSG, gen_default_gf_sink_({predefine_dir,"record","mq_msg",".txt"},1024*512*1,100));
    // regi_gf_sink_to_logger_(REC_TASK_RESULT, gen_default_gf_sink_({predefine_dir,"record","subtask_result",".txt"},1024*512*1,100));
    //regi all
    regi_all_logger_();
    //dynamic config
    //printf("out logger cfg!\n");
    spdlog::set_pattern(DEFAULT_LOGGER_PATTERN);
    spdlog::set_level(spdlog::level::trace);
    //can't same file diff file sinks
    //update will call reint of gfsink and trigger create file
    //complete log_dir_st should be search by rotate update, current before rotate, just to assign member var
    set_cur_log_dir_st(log_dir_st{predefine_dir, "00", "task"});
    // cur_log_dir_st_ = log_dir_st{predefine_dir, "00", "task"};
    // update_log_dir_(log_dir_st{"./log", "0", "task1"});
    // update_log_dir_pattern_(4, 1024*1);
    update_log_dir_pattern_(20, 1024*150);
}
NAMESPACE_END(gf)