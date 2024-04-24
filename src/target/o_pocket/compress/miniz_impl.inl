#pragma once
#include <iostream>
#include "filesystem_test.hpp"
#include "log.h"
#include "miniz.h"
#include "filesystem_impl.inl"


class MinizCompressFile {
public:
    MinizCompressFile(const std::string& output_zip_file);
    ~MinizCompressFile();

    //if have same root path, to append by relative path, either to extract file or dir append to root dir
    //open_relative append expect:
    //if directory
    //check if exist target folder or file in zip archive by mz_zip_reader_locate_file, then to add
    //should using if contain root path instead of using relative path
    //root path: /a/b
    //input path: /a/b/c => recursive zip root: c  base: /a/b
    //input path: /a/b =>recursive zip root: .  base:/a/b(current)
    //input path: /a/c => recursive zip root: . base:/a/c(current)
    //input path: /a/b/e/f => recursive zip root:  e/f  base: /a/b
    //if regular file
    //input path: /a/b/c.txt ==> base:/a/b  fiel: c.txt

    //open_directy append expeact:
    //if directory
    //check if exist target file in zip archive by mz_zip_reader_locate_file, then to add
    //input path: /a/b/c => recursive zip root: c(filename) base: /a/b
    //input path: /a/c/d => recursive zip root: d(filename) base: /a/c
    //if regular file
    //input path: /a/b/c.txt => recursive zip root: c.txt 
    int append_direct(const std::string& input_file_or_dir, const bool true_best_speed_false_best_compress);
    int append_relative(const std::string& input_file_or_dir, const std::string& relative_root_path, const bool true_best_speed_false_best_compress);
    static int recursive_decompress(const std::string& input_filename, const fs::path& output_directory, bool is_strip_root_dir = false);

private:
    int init_();
    int uninit_();
    mz_zip_archive miniz_handle_;
    fs::path output_file_path_;
};

inline MinizCompressFile::MinizCompressFile(const std::string& output_zip_file){
    output_file_path_ = fs::path(output_zip_file);
    if (fs::exists(output_file_path_)) {
        fs::remove_all(output_file_path_);
    }
    init_();
}

inline MinizCompressFile::~MinizCompressFile(){
    uninit_();
}

inline int MinizCompressFile::init_() {
    memset(&miniz_handle_, 0, sizeof(miniz_handle_));
    if (!mz_zip_writer_init_file(&miniz_handle_, output_file_path_.string().c_str(), 0)) {
        return -1;
    }
    return 0;
}

inline int MinizCompressFile::uninit_() {
    mz_zip_writer_finalize_archive(&miniz_handle_);
    mz_zip_writer_end(&miniz_handle_);
    return 0;
}

inline int MinizCompressFile::append_direct(const std::string& input_file_or_dir, const bool true_best_speed_false_best_compress) {
    //directory process
    //尾部分割符问题涉及到提取父级目录和文件名的问题
    //https://stackoverflow.com/questions/36941934/parent-path-with-or-without-trailing-slash
    //   /a/b/    /a/b/.   /a/b
    //tril with '/' is as directory on path string mean, parent_path will get current path just strip '/' 
    //tril with no '/' is as filename on path string mean
    //so need proeccess end of input file string, if input string have '/'
    //scheme1: by manual, to triat string path
    //scheme2: split one virtual file name to input dir path, then to strip filename or get parent path
    //scheme3: directly using filesystem api to strip 
    //strip backlash '/'
    try {
        int compress_level = true_best_speed_false_best_compress ? MZ_BEST_SPEED : MZ_BEST_COMPRESSION;
        fs::path input_file = fs::absolute(input_file_or_dir);
        input_file = FsImpl::normal_path(input_file);

        if (!fs::exists(input_file)) {
            return -1;
        }
        if (fs::is_regular_file(input_file)) {
            fs::path archive_path = input_file.filename();
            int idx = mz_zip_reader_locate_file(&miniz_handle_, archive_path.string().c_str(), nullptr, 0);
            if (idx >= 0) {
                //is exist arhived
                return -2;
            }
            //start append MZ_BEST_SPEED MZ_BEST_COMPRESSION
            if (!mz_zip_writer_add_file(&miniz_handle_, archive_path.string().c_str(), input_file.string().c_str(), NULL, 0, compress_level)) {
                return -3;
            }
            return 0;
        }
        if (!fs::is_directory(input_file)) {
            return -4;
        }
        
        std::string base_path = input_file.parent_path();
        for (const auto& entry : fs::recursive_directory_iterator(input_file)) {
            fs::path archive_path = fs::relative(entry.path(), base_path);
            if (!fs::is_directory(entry)) {
                int idx = mz_zip_reader_locate_file(&miniz_handle_, archive_path.string().c_str(), nullptr, 0);
                if (idx >= 0) {
                    //is exist arhived
                    return -2;
                }
                if (!mz_zip_writer_add_file(&miniz_handle_, archive_path.c_str(), entry.path().c_str(), NULL, 0, compress_level)) {
                    return -5;
                }
            }
        }
    }
    catch (const std::exception& e) {
        return -10;
    }
    return 0;
}

inline int MinizCompressFile::append_relative(const std::string& input_file_or_dir, const std::string& input_relative_root_path, const bool true_best_speed_false_best_compress) {
    try {
        int compress_level = true_best_speed_false_best_compress ? MZ_BEST_SPEED : MZ_BEST_COMPRESSION;
        fs::path input_file = fs::absolute(input_file_or_dir);
        fs::path relative_root_path = fs::absolute(input_relative_root_path);
        input_file = FsImpl::normal_path(input_file);

        if (!fs::exists(input_file)) {
            return -1;
        }
        bool is_contain_root_path = (input_file.native().find(relative_root_path.native()) != std::string::npos);

        if (fs::is_regular_file(input_file)) {
            //if contian root path, using relative root path as archive path, otherwise, using direct folder
            fs::path archive_path;
            if (is_contain_root_path) {
                archive_path = fs::relative(input_file, relative_root_path);
            }
            else {
                archive_path = input_file.filename();
            }
            int idx = mz_zip_reader_locate_file(&miniz_handle_, archive_path.string().c_str(), nullptr, 0);
            if (idx >= 0) {
                //is exist arhived
                return -2;
            }
            //start append
            if (!mz_zip_writer_add_file(&miniz_handle_, archive_path.string().c_str(), input_file.string().c_str(), NULL, 0, compress_level)) {
                return -3;
            }
            return 0;
        }
        if (!fs::is_directory(input_file)) {
            return -4;
        }
        //directory process
        fs::path base_path;
        if (is_contain_root_path) {
            base_path = relative_root_path;
        }
        else {
            base_path = input_file.parent_path();
        }
        for (const auto& entry : fs::recursive_directory_iterator(input_file)) {
            fs::path archive_path = fs::relative(entry, base_path);
            if (!fs::is_directory(entry)) {
                int idx = mz_zip_reader_locate_file(&miniz_handle_, archive_path.string().c_str(), nullptr, 0);
                if (idx >= 0) {
                    //is exist arhived
                    return -2;
                }
                SLOGW("will append archive path:{}, entry:{}, base_path:{}, is contian root:{}, relative:{}", archive_path.c_str(), entry.path().c_str(), base_path.c_str(), is_contain_root_path, relative_root_path.c_str());
                if (!mz_zip_writer_add_file(&miniz_handle_, archive_path.c_str(), entry.path().c_str(), NULL, 0, compress_level)) {
                    return -5;
                }
            }
        }
    }
    catch (const std::exception& e) {
        return -10;
    }
    return 0;
}
//能满足使用，但还需要进行异常判断，如磁盘空间满无法进行读写，这部分逻辑由外围函数实现
//提供处理模式: 如当存在一层根目录时，提供选项决定是否去除根目录
//覆盖策略, 要想清空目标文件夹则额外组合操作
inline int MinizCompressFile::recursive_decompress(const std::string& input_filename, const fs::path& output_directory, bool is_strip_root_dir) {
    bool is_single_root_dir = false;
    fs::path single_root_path;
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));
    try {
        //check
        if (!fs::exists(input_filename)) {
            return -1;
        }
        fs::create_directories(output_directory);

        //miniz start
        mz_bool miniz_status = mz_zip_reader_init_file(&zip_archive, input_filename.c_str(), 0);
        if (!miniz_status) {
            return -1;
        }
        size_t file_num = mz_zip_reader_get_num_files(&zip_archive);
        for (size_t idx = 0; idx < file_num; idx++) {
            mz_zip_archive_file_stat file_stat;
            if (!mz_zip_reader_file_stat(&zip_archive, idx, &file_stat)) {
                return -2;
            }
            fs::path output_path = output_directory / fs::path(file_stat.m_filename);
            //chekc if dir
            if (mz_zip_reader_is_file_a_directory(&zip_archive, idx)) {
                //check first file is dir
                if (!is_single_root_dir && idx == 0) {
                    is_single_root_dir = true;
                    single_root_path = output_directory / file_stat.m_filename;
                }
                //recursive create
                fs::create_directories(output_path);
                SLOGD("create dir:{}", output_path.string());
                continue;
            } 
            // confirm parent folder exist
            fs::create_directories(output_path.parent_path());
            // decompress file to target path
            miniz_status = mz_zip_reader_extract_to_file(&zip_archive, idx, output_path.string().c_str(), MZ_TRUE);
            if (!miniz_status) {
                return -3;
            }
        }

        // if exist single root dir and enable this flag, to strip
        //rename way is fast, but required new name is not exist
        //copy and delete is last way
        // /a/b/sub_root/content ===> /a/b/sub_root > /a/tmp_xx_uniform > clean /a/b   > rename /a/tmp_xx_uniform  /a/b
        #if 1
        if (is_strip_root_dir && is_single_root_dir) {
            SLOGW("enter strip root dir, single root path:{}, output directory:{}", single_root_path.string(), output_directory.string());
            //1. dst dir contain the src dir,  /var/TESTBED/testbed_objective/testbed_objective to /var/TESTBED
            //2. dst dir not empty
            int ret = FsImpl::move_file(single_root_path, output_directory, true, 1, 0);
            if (ret) {
                SLOGE("single root path:{}, output_directory:{}", single_root_path.string(), output_directory.string());
                return -7;
            }
        }
        #endif

        //miniz end
        mz_zip_reader_end(&zip_archive);
        return 0;
    }
    catch (const std::exception& e) {
        return -10;
    }
    
    
}

