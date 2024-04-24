CMAKE_MINIMUM_REQUIRED(VERSION 3.4.2)

PROJECT(${exe_name})
include(${cmake_file_root_ab}/color.cmake)
include(${cmake_file_root_ab}/module.cmake)
SET(CURRENT_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CURRENT_PROJECT_PATH}/src src_list)


generate_module("m_erc" 
    SP_INC 
        ${CURRENT_PROJECT_PATH}/include
    SP_LIB 
        "NON"
    SP_SRC 
        ${src_list}
)