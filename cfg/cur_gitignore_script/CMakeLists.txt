CMAKE_MINIMUM_REQUIRED(VERSION 3.4.2)
###load cmake script dependece
macro(define_include_var v_name value_default)
    if(NOT DEFINED ${v_name})
        message(STATUS "not defined ${v_name}, set by default[${value_default}]")
        set(${v_name} ${value_default} CACHE STRING "xx")
    endif()
    message(STATUS "defined ${v_name}=${${v_name}}")
endmacro()

define_include_var(cmake_file_root "xxx")
if(IS_DIRECTORY "${cmake_file_root}")
  message(STATUS "cmake_file_root:${cmake_file_root} exists.")
else()
  message(FATAL_ERROR "cmake_file_root:${cmake_file_root} does not exist.")
endif()
get_filename_component(cmake_file_root_ab ${cmake_file_root} ABSOLUTE)
message(STATUS "cmake_file_root_ab:${cmake_file_root_ab}.")
include("${cmake_file_root_ab}/color.cmake")
include("${cmake_file_root_ab}/module.cmake")

###compile flag
set(CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS(-std=gnu++11)
add_definitions(-w)
add_definitions(-DSPDLOG_COMPILED_LIB)
# add_compile_options(-j4)
# add_definitions(-DSPDLOG_COMPILED_LIB)
# add_definitions(-fno-elide-constructors)  

###receive custom variable
define_var(root_project_name "jf_project")
define_var(exe_name "EXE")
define_var(sys_name "qnx")#qnx    linux_arm linux_x64
define_var(build_dir "${CMAKE_CURRENT_SOURCE_DIR}/build" "ON")
# define_var(custom_cmake_script_dir "${cmake_file_root_ab}")
define_var(output_dir_root "${CMAKE_CURRENT_SOURCE_DIR}/out" "ON")
define_var(for_public_dir_path "/home/xjf2613/code-space/QNX/qnx-sdk-project-20220228/FOR-PUBLIC" "ON")
define_var(other_module_list "xxxxx;12324;24324;3435")
define_var(build_target_list "")
print_list_with_index(other_module_list)

# foreach_add_sub(other_module_list ${build_dir} )
PROJECT(${root_project_name})
foreach_add_sub_by_head_list(${build_dir} "src/module"
"m_jsoncpp" 
"m_sqlite" 
"m_mongoose"
"m_mosquitto" 
"m_rabbitmq" 
"m_sdplog"
"m_zip" 
"m_mytool"
"m_curl"
"m_internal"
"m_component"
"m_gtest"
"m_samba"
)
foreach_add_sub_by_head_list(${build_dir} "src/target"
# "o_compile_target"
# "o_fast_i30testbed"
# "o_log_broker"

# "o_main_i30service"
# "o_test_file_trainsformer"
# "o_test_mqtt"
# "o_test_rabbitmq"
# "o_test_curl"
# "o_log_integrate"
# "o_verify_system_return"
# o_test_gtest
# "o_main_service"
# "o_service"
${build_target_list}
)


