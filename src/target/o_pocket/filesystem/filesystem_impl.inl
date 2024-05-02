#pragma once
#include <iostream>
#include "filesystem_test.hpp"
#include "log.h"
#define START_NAMESPACE(name) namespace name{
#define END_NAMESPACE(name) }

START_NAMESPACE(fs_impl)
//https://github.com/richgel999/miniz.git
// inline fs::path normal_path(const fs::path& input_file) {
//     //check file if exist, if non, to exception
//     if (!fs::exists(input_file)) {
//         SLOGE("input file is not exist, path:{}", input_file.c_str());
//         std::string msg = input_file.string() + " file not exist";
//         throw std::runtime_error(msg);
//     }
//     if (fs::is_directory(input_file)) {
//         SLOGD("input file:{}, is directory, will append file name to extract parent path for strip backlash", input_file.c_str());
//         input_file /= "file.txt";
//         input_file = input_file.lexically_normal();
//         fs::path return_path = input_file.parent_path();
//         SLOGD("get directory normal path:{}", return_path.c_str());
//         return return_path;
//     }
//     if (fs::is_regular_file(input_file)) {
//         SLOGD("get regular file normal path:{}", return_path.c_str());
//         fs::path return_path = input_file.lexically_normal();
//         return return_path;
//     }
//     std::string msg = input_file.string() + " file not regular file or directory";
//     throw std::runtime_error(msg);
// }
inline bool path_contain(const fs::path& path1, const fs::path& path2) {
    // Normalize the paths
    auto cpath1 = fs::canonical(path1);
    auto cpath2 = fs::canonical(path2);

    // Check if path1 contains path2
    return cpath2.native().find(cpath1.native()) == 0;
}
inline fs::path normal_path(const fs::path& in_input_file) {
    //check file if exist, if non, to exception
    fs::path input_file = in_input_file;
    if (!fs::exists(input_file)) {
        SLOGE("input file is not exist, path:{}", input_file.c_str());
        std::string msg = input_file.string() + " file not exist";
        throw std::runtime_error(msg);
    }
    if (fs::is_directory(input_file)) {
        SLOGD("input file:{}, is directory, will append file name to extract parent path for strip backlash", input_file.c_str());
        input_file /= fs::path("file.txt");
        input_file = input_file.lexically_normal();
        fs::path return_path = input_file.parent_path();
        SLOGD("get directory normal path:{}", return_path.c_str());
        return return_path;
    }
    if (fs::is_regular_file(input_file)) {
        // SLOGD("get regular file normal path:{}", input_file.c_str());
        fs::path return_path = input_file.lexically_normal();
        return return_path;
    }
    std::string msg = input_file.string() + " file not regular file or directory";
    throw std::runtime_error(msg);
}
//1. check src file is dir or file, if dir, third argument is valid
//2. if src file is dir, is_contain_src_folder = true, move src dir to dst folder as sub dir
//3. if src file is file, just move file to dst_folder, ignore third argument
//4. if sub target file is exist, choice if to override
//default behavior
//https://en.cppreference.com/w/cpp/filesystem/remove
// inline int 
//!!! 起始需要检查源文件和目标文件是否存在
//!!! 所有的remove all 行为都要考虑，是否源目录与目标目录是否是包含关系, 典型的有将子文件夹重命名为父文件夹(提取子文件夹的内容到父文件夹), 一旦使用rename模式，会将src文件夹删除
// rename 操作成功的基础是 new name 不存在

//常见问题: 1. dst dir contain the src dir 2. dst dir not empty, it's exist 3.src dir contian the dst dir
//0. get dst and src dir path relationship, distingguishing bad situation to return error 
//1. rename way :  转移src目录到安全路径，再处理目标目录和冲突目录
//1.1  if(situation 1){to gen target path + gen an not exist tmp path, rename src to tmp path + rm target path + rename to target path}
//1.2 if(situdation 2){to gen target path + gen an not exist tmp path, rename src to tmp path + rm target path + rename to target path}
//1.3 if(situation 3 check if src dir contian dst dir, to return error)
//2. copy and delete way
//2.1 拷贝 + 删除
//2.2 拷贝 + 删除
//2.3 报错
inline int move_file(const std::string& in_src_file, const std::string& dst_folder, const bool to_rename_or_copy, const bool to_override, const bool to_contain_src_folder) {
    try {
        //check file if exist
        if (!fs::exists(in_src_file)) {
            return -1;
        }

        //absolute
        fs::path src_file = fs::absolute(in_src_file);
        src_file = normal_path(src_file);

        //check file or folder
        if (fs::is_regular_file(src_file)) {
            fs::path src_file_path(src_file);
            fs::path dst_file_path = fs::path(dst_folder) / (src_file_path.filename());
            //no override and file exist, to do noting
            if (fs::exists(dst_file_path) && !to_override) {
                //warning log
                //....
                return 0;
            }
            //bold clean
            fs::remove(dst_file_path);
            //to rename or copy
            if (to_rename_or_copy) {
                //rename
                fs::rename(src_file_path, dst_file_path);
            }
            else {
                //copy
                fs::copy_file(src_file_path, dst_file_path);
            }
            return 0;
        }

        //strip not folder
        if (!fs::is_directory(src_file)) {
            //warning log
            //..
            return -1;
        }
        //process folder
        //gen dst folder 
            //!!!! if remove folder is contain t
        fs::path dst_folder_path(dst_folder);
        fs::path src_folder_path(src_file);
        if (to_contain_src_folder) {
            //append src_folder
            dst_folder_path = fs::path(dst_folder) / src_folder_path.filename();
        }
        //may lass two layer dir
        fs::create_directories(dst_folder_path);
        dst_folder_path = normal_path(dst_folder_path);
        //check rename or copy, because rename need target not exist (need clear), copy should prepare target parent folder
        if (to_rename_or_copy) {
            //situation3: check if src contain dst path, if true to return error
            if (path_contain(src_folder_path, dst_folder_path)) {
                SLOGE("src folder:{} contain dst folder:{}", src_folder_path.string(), dst_folder_path.string());
                return -2;
            }
            //situation1 and situation2: 
            //!!!! if remove folder is contain the src folder?  /a/b/c rename /a/b
            //first check if contian relativeship, if is not to remove all 
            //需要考虑无法创建目录
            bool is_dst_contian_src = (src_folder_path.native().find(dst_folder_path.native()) != std::string::npos);
            if (is_dst_contian_src) {
                //need convet to ablsolute for avoid relative path which contain .
                std::string tmp_path = fs::absolute(dst_folder_path.parent_path());;
                while (fs::exists(tmp_path)) {
                    tmp_path = tmp_path / fs::path("tmp_for_name");
                }
                fs::create_directories(tmp_path);
                fs::remove_all(tmp_path);
                //get the not exist tmp path, and using by temp rename
                SLOGW("get tmp path :{}, src:{}, using by rename\n", tmp_path.c_str(), src_folder_path.string().c_str());
                // fs::create_directories(tmp_path);
                fs::rename(src_folder_path, fs::path(tmp_path));
                //update
                src_folder_path = fs::path(tmp_path);
            }
            //need to warnning, will remove dst folder and then to rename
            fs::remove_all(dst_folder_path);
            fs::rename(src_folder_path, dst_folder_path);
            return 0;
        }
        //copy process
        if (to_override) {
            fs::copy(src_folder_path, dst_folder_path, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
        }
        else {
            fs::copy(src_folder_path, dst_folder_path, fs::copy_options::skip_existing | fs::copy_options::recursive);
        }
        fs::remove_all(src_folder_path);
    }
    catch (const std::exception& e) {
        SLOGE("move_file exception: what{}\n", e.what());
        return -10;
    }

    //final
    return 0;
}

inline int copy_file(const std::string& src_file, const std::string& dst_folder, const bool to_override, const bool to_contain_src_folder) {
    try {
        if (!fs::exists(src_file)) {
            return -1;
        }

        fs::path dst_folder_path = fs::path(dst_folder);

        if (!fs::exists(dst_folder_path)) {
            fs::create_directories(dst_folder_path);
        }

        if (fs::is_regular_file(src_file)) {
            fs::path destination_file = dst_folder_path / fs::path(src_file).filename();
            if (!to_override && fs::exists(destination_file)) {
                // print warning
                // ....
                return 0;
            }
            fs::copy_file(src_file, destination_file, fs::copy_options::overwrite_existing);
            return 0;
        }

        if (fs::is_directory(src_file)) {
            fs::path destination_dir = dst_folder_path;
            if (to_contain_src_folder) {
                destination_dir = dst_folder_path / fs::path(src_file).filename();
                fs::create_directories(destination_dir);
            }
            if (to_override) {
                fs::copy(src_file, destination_dir, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
            }
            else {
                fs::copy(src_file, destination_dir, fs::copy_options::skip_existing | fs::copy_options::recursive);
            }
        }
    }
    catch (const std::exception& e) {
        return -10;
    }

    return 0;
}

inline int clean_folder(const std::string& src_folder) {
    try {
        if (!fs::exists(src_folder)) {
            fs::create_directories(src_folder);
        }
        else {
            fs::remove_all(src_folder);
            fs::create_directories(src_folder);
        }
    }
    catch (const std::exception& e) {
        return -10;
    }

    return 0; 
}

inline int delete_file(const std::string& src_file, const bool to_contain_src_folder) {
    try {
        if (!fs::exists(src_file)) {
            return -1;
        }
        if (fs::is_regular_file(src_file)) {
            fs::remove(src_file);
            return 0;
        }
        if (fs::is_directory(src_file)) {
            fs::remove_all(src_file);
            if (to_contain_src_folder) {
                fs::create_directories(src_file);
            }
        } 
    }
    catch (const std::exception& e) {
        SLOGE("delete file fail! what:{}", e.what());
        return -10; 
    }
    return 0;
}

inline int obtain_file_space(const std::string& src_file, size_t& out_size_byte, size_t& out_folder_num, size_t& out_file_num) {
    try {
        out_size_byte = 0;
        out_folder_num = 0;
        out_file_num = 0;
 
        if (!fs::exists(src_file)) {
            return -1;
        } 
        if (fs::is_regular_file(src_file)) {
            out_size_byte = fs::file_size(src_file);
            ++out_file_num;
            return 0; 
        }
        if (fs::is_directory(src_file)) {
            //root dir ++
            ++out_folder_num;
            for (const auto& entry : fs::recursive_directory_iterator(src_file)) {
                if (fs::is_regular_file(entry.path())) {
                    ++out_file_num;
                    out_size_byte += fs::file_size(entry.path());
                    continue;
                }
                ++out_folder_num;
            }
        }
    } catch (const std::exception& e) {
        return -10; 
    }
    return 0;
}

//if not folder to return error
inline int obtain_folder_remain_space(const std::string& src_folder, size_t& out_space_byte) {
    try {
        if (!fs::is_directory(src_folder)) {
            return -1; 
        }

        uintmax_t total_available_space = fs::space(src_folder).available;
        out_space_byte = total_available_space;
    } catch (const std::exception& e) {
        return -10; 
    }

    return 0; 
}


END_NAMESPACE(fs_impl)

class FsImpl {
public:
    FsImpl() = default;
    ~FsImpl() = default;

    static fs::path normal_path(const fs::path& input_file) {
        return fs_impl::normal_path(input_file);
    };

    static int move_file(const std::string& in_src_file, const std::string& dst_folder, const bool to_rename_or_copy, const bool to_override, const bool to_contain_src_folder) {
        return fs_impl::move_file(in_src_file, dst_folder, to_rename_or_copy, to_override, to_contain_src_folder);
    };

    static int copy_file(const std::string& src_file, const std::string& dst_folder, const bool to_override, const bool to_contain_src_folder) {
        return fs_impl::copy_file(src_file, dst_folder, to_override, to_contain_src_folder);
    };

    static int clean_folder(const fs::path& src_folder) {
        return fs_impl::clean_folder(src_folder);
    };

    static int delete_file(const std::string& src_file, const bool to_contain_src_folder) {
        return fs_impl::delete_file(src_file, to_contain_src_folder);
    };

    static int obtain_file_space(const std::string& src_file, size_t& out_size_byte, size_t& out_folder_num, size_t& out_file_num) {
        return fs_impl::obtain_file_space(src_file, out_size_byte, out_folder_num, out_file_num);
    };

    static int obtain_folder_remain_space(const std::string& src_folder, size_t& out_space_byte) {
        return fs_impl::obtain_folder_remain_space(src_folder, out_space_byte);
    };
};