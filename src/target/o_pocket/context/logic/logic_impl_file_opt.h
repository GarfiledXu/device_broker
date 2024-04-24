#pragma once
#include <mutex>
#include <string>

#include "log.h"

#include "miniz_impl.inl"
#include "filesystem_impl.inl"
#include "cli11_base.h"
#include "time_interval.inl"

#include "samba_transfer.h"

int update_testbed_and_replace(const std::string& in_url, const std::string& dst_dir_path, const std::string& cache_dir_path, std::map<std::string, std::string> replace_list);


int unzip_testbed(const std::string& in_url, const std::string& dst_dir_path, const std::string& cache_dir_path);
int mv_file_to_target(const std::string& src_file, const std::string& dst_dir, const bool is_check_src_file);

int query_file_size(const std::string& src_file, std::size_t& out_size_byte, std::size_t& out_folder_num, std::size_t& out_file_num);
int query_dir_remain_space(const std::string& src_dir, std::size_t& out_size_byte);
int http_download(const std::string& in_url, const std::string& target_local_file);
int http_file_size(const std::string& in_url, std::size_t& out_file_size);
int smb_download(const std::string& url, const std::string& dst_file, const std::string& user_name, const std::string& work_group, const std::string& passwd);
int url_space_measure(const std::string& in_url, const std::string& dst_dir_path);