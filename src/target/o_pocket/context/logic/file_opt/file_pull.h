#pragma once

#include <string>
#include <vector>
#include "logic_impl_file_opt.h"
#include "samba_transfer.h"
#include "log.h"


int smb_remote_upload_file(const std::string& in_url, std::vector<std::string> in_local_file_list, const std::string& in_smb_usr, const std::string& in_smb_passwd);

int find_file_list_by_suffix(const std::string& root_dir, std::vector<std::string>& out_vec_file_path, const std::string& extension);

int smb_remote_upload_file_by_suffix(const std::string& in_url, const std::string& in_local_dir, const std::string& in_file_suffix,  const std::string& in_smb_usr, const std::string& in_smb_passwd);
