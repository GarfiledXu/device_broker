
CMAKE_MINIMUM_REQUIRED(VERSION 3.4.2)

PROJECT(${exe_name})
include(${cmake_file_root_ab}/color.cmake)
include(${cmake_file_root_ab}/module.cmake)
SET(CURRENT_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CURRENT_PROJECT_PATH}/src src_list)

set(root_exe_name "new_service")
## websocket
set(cur_exe_name1 "TESTBED_PLATFORM")
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")
configure_file(${cmake_file_root_ab}/compile_info.h.in ${CURRENT_PROJECT_PATH}/compile_info.h)
file(WRITE ${output_dir_root}/${root_exe_name}/${cur_exe_name1}/compile_info.txt "${BUILD_DATE}\n")

# aux_source_directory(context context_src_list)
add_executable(${cur_exe_name1} 
main.cpp
log/log.cpp
)
target_include_directories(${cur_exe_name1} PRIVATE 
.
log
)
add_module_list(${cur_exe_name1} 
# "m_rabbitmq"
# "m_mongoose" 
# # "m_internal"

# "m_wheel"
# "m_sqlite"
# "m_jsonhpp"
# "m_component"
# "m_gtest"
"m_fmt"
"m_filesystem"
"m_spdlog" 
# "m_miniz"
# "m_samba"
# "m_gf_fs"
# "m_curl"
"m_cli11"
# "m_zip"
# "m_wheel"
)
add_build_root_dir(${cur_exe_name1} "${output_dir_root}/${root_exe_name}/${cur_exe_name1}")
prepare_folder("${output_dir_root}")
target_link_libraries(${cur_exe_name1} PRIVATE ${system_lib} 
 socket
#  libshutdown.a
#  shutdown
# pthread
 )
forward(${cur_exe_name1} "True" "${output_dir_root}/${root_exe_name}/${cur_exe_name1}/compile_info.txt" ${CMAKE_CURRENT_SOURCE_DIR})
backward(${cur_exe_name1} "True" "${output_dir_root}/${root_exe_name}/${cur_exe_name1}/compile_info.txt" ${CMAKE_CURRENT_SOURCE_DIR})

# get_target_property(EXE_PATH ${cur_exe_name1} RUNTIME_OUTPUT_DIRECTORY)
# file(COPY ${EXE_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(RENAME out/out_700/new_service/mock_testbed/${cur_exe_name1} out/out_700/new_service/mock_testbed/TESTBED_PLATFORM)
