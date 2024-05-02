
CMAKE_MINIMUM_REQUIRED(VERSION 3.24.2)

PROJECT(${exe_name})
include(${cmake_file_root_ab}/color.cmake)
include(${cmake_file_root_ab}/module.cmake)
SET(CURRENT_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CURRENT_PROJECT_PATH}/src src_list)

# set(system_name "qnx700")

set(cur_inc 
    ${CURRENT_PROJECT_PATH}/include
    ${CURRENT_PROJECT_PATH}/include/rabbitmq-c
)
set(cur_lib 
${CURRENT_PROJECT_PATH}/lib/qnx700/librabbitmq.so.0.14.0
) 
set(cur_src "")

string(TOLOWER ${system_name} cur_system_name OUTPUT_VARIABLE)

if(cur_system_name STREQUAL "android")

elseif(system_name STREQUAL "qnx710")
## qnx710
set(cur_lib 
# ${CURRENT_PROJECT_PATH}/lib/qnx710/librabbitmq.so.0.14.0
${CURRENT_PROJECT_PATH}/lib/qnx710/librabbitmq.a
)
else()
## 默认qnx700
endif()

generate_module("m_rabbitmq" 
    SP_INC 
        ${cur_inc}
    SP_LIB 
        ${cur_lib}
    SP_SRC 
        "NON")



