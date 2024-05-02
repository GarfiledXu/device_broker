
CMAKE_MINIMUM_REQUIRED(VERSION 3.4.2)

PROJECT(${exe_name})
include(${cmake_file_root_ab}/color.cmake)
include(${cmake_file_root_ab}/module.cmake)
SET(CURRENT_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CURRENT_PROJECT_PATH}/src src_list)

string(TOLOWER ${system_name} cur_system_name OUTPUT_VARIABLE)

set(cur_inc 
    ${CURRENT_PROJECT_PATH}/inc
)
set(cur_lib 
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libsmbclient.so
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libtalloc.so
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libtdb.so
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libtevent.so
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libwbclient.a
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libaddns.a
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libnetapi.so
        ${CURRENT_PROJECT_PATH}/lib/qnx700/libsmbsharemodes.so
) 
set(cur_src "")

if(cur_system_name STREQUAL "android")

elseif(system_name STREQUAL "qnx710")
## qnx710
set(cur_lib 
        ${CURRENT_PROJECT_PATH}/lib/qnx710/libsmbclient.so.0
        ${CURRENT_PROJECT_PATH}/lib/qnx710/libtalloc.so.2
        ${CURRENT_PROJECT_PATH}/lib/qnx710/libtdb.so.1
        ${CURRENT_PROJECT_PATH}/lib/qnx710/libtevent.so.0
) 
else()
## 默认qnx700
endif()


generate_module("m_samba" 
    SP_INC 
        ${cur_inc}
    SP_LIB 
        ${cur_lib}
    SP_SRC 
        "NON")


