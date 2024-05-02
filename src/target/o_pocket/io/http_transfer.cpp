#include "log.h"
#include "gf_fs_curl/gf_rfs_curl.h"
#include "time_interval.inl"

using namespace gf::filesystem::remote;

static remote_filesystem* base_filesystem = new gf_rfs_curl(
    [](int level, const std::string& msg) {
        if (level == RFS_CURL_LOG_ERROR) {
            SLOGE("{}", msg);
        }
        else if (level == RFS_CURL_LOG_INFO) {
            SLOGI("{}", msg);
        }
        else {
            SLOGD("{}", msg);
        }
    }
);

int http_download(const std::string& in_url, const std::string& target_local_file) {
    TimeInterval<> time_interval{};
    auto cur_ret = base_filesystem->download_file(in_url, target_local_file);
    if (cur_ret.err_type != RETURN_SUCCESS) {
        SLOGE("down_update_file fail! can't down file, url:{}, located path:{}, ret:{}", in_url.c_str(), target_local_file.c_str(), cur_ret.err_value);
        // return erc(-1);
        return -1;
    }
    SLOGD("download url:{} to local:{} success, cost time: [{}] ms", in_url, target_local_file, time_interval.get_interval_ms());
    return 0;
}

int http_file_size(const std::string& in_url, std::size_t& out_file_size) {
    TimeInterval<> time_interval{};
    out_file_size = 0;
    auto cur_ret = base_filesystem->file_size(in_url);
    if (cur_ret.err_type != RETURN_SUCCESS) {
        SLOGE("http_file_size fail! url:{}, ret:{}", in_url, cur_ret.err_value);
        return -1;
    }
    out_file_size = cur_ret.custom;
    SLOGD("http_file_size url:{}, get file size:{} success, cost time: [{}] ms", in_url, out_file_size, time_interval.get_interval_ms());
    return 0;
}