#include "file_clear.h"

int clear_file(std::vector<std::string> file_list)
{
    int ret = 0;
    for (auto& cur_file : file_list) {
        ret = FsImpl::delete_file(cur_file, false);
        if (ret) {
            SLOGE("delete file fail! ret:{}, file:{}", ret, cur_file);
            return -1;
        }
    }
    return 0;
}
