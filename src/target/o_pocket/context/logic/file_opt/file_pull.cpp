#include "file_pull.h"

int smb_remote_upload_file(const std::string& in_url, std::vector<std::string> in_local_file_list, const std::string& in_smb_usr, const std::string& in_smb_passwd)
{

    SafeSambaTrasfer* smb_mg = new SafeSambaTrasfer(in_smb_usr, in_smb_passwd);

    auto local_file_path = "/var/run";
    int ret = smb_mg->UploadAll(in_url, local_file_path); 

    // for (auto& local_file_path : in_local_file_list) {
        // int ret = smb_mg->UploadAll(in_url, local_file_path); 
        if (ret) {
            SLOGE("upload file fail! smb upload all return:{}, upload file:{} to url:{}", ret, local_file_path, in_url);
            delete smb_mg;
            return -1;
        }
        SLOGD("upload file success! smb upload file:{} to url:{}", local_file_path, in_url);
    // }

    delete smb_mg;
    return 0;

}
int find_file_list_by_suffix(const std::string& root_dir, std::vector<std::string>& out_vec_file_path, const std::string& extension) {

    fs::path root_path(root_dir);
    
    if (!fs::exists(root_path) || !fs::is_directory(root_path)) {
        std::cerr << "Error: Root directory does not exist or is not a directory." << std::endl;
        return -1;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(root_path)) {
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == extension) {
            out_vec_file_path.push_back(entry.path().string());
        }
    }

    SLOGD("find file list, size:{}", out_vec_file_path.size());
    
    return 0;

}

int smb_remote_upload_file_by_suffix(const std::string& in_url, const std::string& in_local_dir, const std::string& in_file_suffix, const std::string& in_smb_usr, const std::string& in_smb_passwd)
{

    std::vector<std::string> upload_file_list;
    int ret = find_file_list_by_suffix(in_local_dir, upload_file_list, in_file_suffix);
    if (ret || (upload_file_list.size() < 1)) {
        SLOGE("find file list empty, ret: {}, dir: {}, file suffix:{}", ret, in_local_dir, in_file_suffix);
        return -1;
    }

    ret = smb_remote_upload_file(in_url, upload_file_list, in_smb_usr, in_smb_passwd);
    if (ret) {
        SLOGE("smb remote upload file fail, ret:{}", ret);
        return -2;
    }

    return 0;

}
