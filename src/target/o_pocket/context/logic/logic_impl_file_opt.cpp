#include "logic_impl_file_opt.h"
//
// #include <sys/shutdown.h>
int update_testbed_and_replace(const std::string& in_url, const std::string& dst_dir_path, const std::string& cache_dir_path, std::map<std::string, std::string> replace_list) {
    int ret = 0;
    ret = unzip_testbed(in_url, dst_dir_path, cache_dir_path);
    if (ret) {
        SLOGE("unzip testbed fail! ret:{}", ret);
        return ret;
    }
    for (auto& cur_pair : replace_list) {
        ret = mv_file_to_target(cur_pair.first, cur_pair.second, false);
        if (ret) {
            SLOGE("mv file to target fail! src:{}, target:{}", cur_pair.first, cur_pair.second);
            return ret;
        }
    }
    // shutdown_system(SHUTDOWN_REBOOT, FLAG_FAST );
    // system("shutdown -S reboot");
    return 0;
}
//test pass
int url_space_measure(const std::string& in_url, const std::string& dst_dir_path)
{
    TimeInterval<> time_interval{};
    int ret = 0;
    //if get file size two large or fail, to warnning and skip contrast with remian space 
    //check url file size x2 > remain sapce kb => warning! or error!
    bool is_contrast = true;
    std::size_t file_size_b = 0;
    std::size_t dir_remain_space_b = 0;
    ret = http_file_size(in_url, file_size_b);
    if (ret || (0 == file_size_b) || (file_size_b > 1000 * 1000 * 1000 * 100)) {
        SLOGW("warning, http_file_size wrong, ret:{}, file size byte:{}, will skip remain space contrast", ret, file_size_b);
        is_contrast = false;
    }
    ret = FsImpl::obtain_folder_remain_space(dst_dir_path, dir_remain_space_b);
    if (ret || (0 == file_size_b)) {
        SLOGW("warning,obtain_folder_remain_space wrong, ret:{}, space kb:{}, will skip remain space contrast", ret, dir_remain_space_b);
        is_contrast = false;
    }
    if (is_contrast) {
        if ((double)file_size_b * 2 / 1000 > dir_remain_space_b) {
            SLOGE("insufficient remaining space, will stop to download file and unzip, file url:{} size byte:{}, dst dir:{}, remain sapce byte:{}",
                in_url, file_size_b, dst_dir_path, dir_remain_space_b);
            return -1;
        }
    }
    SLOGI("dst dir remain space check pass, get url:{} file size byte:{}, dst dir:{}, remain space byte:{}, cost time: [{}] ms",
            in_url, file_size_b, dst_dir_path, dir_remain_space_b, time_interval.get_interval_ms());
    return 0;
}

//test pass
int unzip_testbed(const std::string& in_url, const std::string& dst_dir_path, const std::string& cache_dir_path)
{
    int ret = 0;
    TimeInterval<> time_interval{};

    //check space
    if (url_space_measure(in_url, dst_dir_path)) {
        SLOGE("will stop unzip testbed, space check not pass");
        return -1;
    }
    
    //prepare dst dir
    SLOGD("start prepare cache dir path:{}", cache_dir_path);
    ret = FsImpl::clean_folder(cache_dir_path);
    if (ret) {
        SLOGE("prepare cache dir fail! path:{}, ret:{}", cache_dir_path, ret);
        return -2;
    }

    //down url to tmp
    std::string tmp_file = fmt::format("{}/{}", cache_dir_path, "tmp.zip");
    SLOGD("start http download url:{}, to local file:{}", in_url, tmp_file);
    ret = http_download(in_url, tmp_file);
    if (ret) {
        SLOGE("http download url fail! ret:{}, url:{}, dst local file:{}", ret, in_url, tmp_file);
        return -3;
    }

    //unzip to dst path
    SLOGD("start unzip file:{} to dst local dir:{}", tmp_file, dst_dir_path);
    ret = MinizCompressFile::recursive_decompress(tmp_file, fs::path(dst_dir_path), true);
    if (ret) {
        SLOGE("decompress zip fail! ret:{}, file:{}, dst dir:{}", ret, tmp_file, dst_dir_path);
        return -4;
    }

    //clean
    SLOGD("start clean cache dir path:{}", cache_dir_path);
    ret = FsImpl::clean_folder(cache_dir_path);
    if (ret) {
        SLOGE("clean cache dir fail! path:{}, ret:{}", cache_dir_path, ret);
        return -5;
    }

    SLOGI("unzip testbed finished! cost time: [{}] ms", time_interval.get_interval_ms());
    return 0;
}

//test pass
int mv_file_to_target(const std::string& src_file, const std::string& dst_dir, const bool is_check_src_file)
{
    TimeInterval<> time_interval{};
    bool file_is_exist = fs::exists(src_file);
    if (!file_is_exist) {
        if (is_check_src_file) {
            SLOGE("mv file to target fail! src file is not exist, path: {}", src_file);
            return -1;
        }
        else {
            SLOGW("mv file, src file not exist, will break operation, path: {}", src_file);
            return 0;
        }
    }
    //mv file
    SLOGD("start mv file src:{} to dst dir:{}", src_file, dst_dir);
    int ret = FsImpl::move_file(src_file, dst_dir, true, true, true);
    if (ret) {
        SLOGE("mv file fail! ret:{}, src:{}, dst dir:{}", ret, src_file, dst_dir);
        return -1;
    }
    SLOGI("mv file finished! cost time: [{}] ms", time_interval.get_interval_ms());
    return 0;
}

int cp_file_to_zip()
{
    //only compress
}

int mv_file_to_zip()
{
    //compress and delete
}

//test pass
int query_file_size(const std::string& src_file, std::size_t& out_size_byte, std::size_t& out_folder_num, std::size_t& out_file_num)
{
    TimeInterval<> time_interval{};
    out_size_byte = 0;
    out_folder_num = 0;
    out_file_num = 0;
    int ret = FsImpl::obtain_file_space(src_file, out_size_byte, out_folder_num, out_file_num);
    if (ret || (0 == out_size_byte)) {
        SLOGE("obtain_file_space fail, ret:{}, size byte:{}, folder num:{}, file num:{}", ret, out_size_byte, out_folder_num, out_file_num);
        return -1;
    }
    SLOGI("obtain_file_space success, ret:{}, size byte:{}, folder num:{}, file num:{}, cost time: [{}] ms", ret, out_size_byte, out_folder_num, out_file_num,
        time_interval.get_interval_ms());
    return 0;
}

//test pass
int query_dir_remain_space(const std::string& src_dir, std::size_t& out_size_byte) {
    TimeInterval<> time_interval{};
    int ret = FsImpl::obtain_folder_remain_space(src_dir, out_size_byte);
    if (ret || (0 == out_size_byte)) {
        SLOGW("warning, get dir remain space size wrong, ret:{}, space kb:{}, will skip remain space contrast", ret, out_size_byte);
        return -1;
    }
    SLOGD("get dir remain space, byte size:{}, cost time: [{}] ms", out_size_byte, time_interval.get_interval_ms());
    return 0;
}


std::mutex smb_mutex;
int smb_init(const std::string& user_name, const std::string& work_group, const std::string& passwd)
{

}
int smb_uninit()
{

}
int smb_stat_query(const std::string& url)
{

}

//test pass
int smb_download(const std::string& url, const std::string& dst_dir, const std::string& user_name, const std::string& work_group, const std::string& passwd)
{
    TimeInterval<> time_interval{};
    SafeSambaTrasfer smb{user_name, passwd};
    int ret = smb.DownloadOne(url, dst_dir);
    if (ret) {
        SLOGE("smb_download fail! ret:{}, url:{}, dst dir:{}, user_name:{}, wg:{}, passwd:{}", ret, url, dst_dir, user_name, work_group, passwd);
        return -1;
    }
    SLOGI("smb download success! ret:{}, url:{}, dst dir:{}, user_name:{}, wg:{}, passwd:{}, cost time: [{}] ms",
        ret, url, dst_dir, user_name, work_group, passwd, time_interval.get_interval_ms());
    return 0;
}

int smb_upload(const std::string src_file, const std::string& dst_url)
{

}

