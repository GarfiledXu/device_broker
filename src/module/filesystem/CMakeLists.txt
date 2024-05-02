# /////////////////////////////////////////////////////////////////////////////////////////////////////////////
# ////                  FOR FFMEPG
# /////////////////////////////////////////////////////////////////////////////////////////////////////////////
# ////                  date:2022.02.24
# /////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMAKE_MINIMUM_REQUIRED(VERSION 3.4.2)
ADD_DEFINITIONS(-std=gnu++11)
PROJECT(${exe_name})
include(${cmake_file_root_ab}/color.cmake)
include(${cmake_file_root_ab}/module.cmake)
SET(CURRENT_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CURRENT_PROJECT_PATH}/src src_list)
#how to resovle the reference relatition of two module
#add one module to another module



# print_module(m_component)
generate_module(m_filesystem 
    SP_INC 
        ${CURRENT_PROJECT_PATH}/inc
        ${CURRENT_PROJECT_PATH}/inc/include
    SP_LIB 
        "NON"
    SP_SRC 
       ${src_list})

# add_module_to_module(m_component m_internal m_zip m_toycv m_ffmpeg)
# print_module(m_component)
