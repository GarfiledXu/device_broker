#include "samba_transfer.h"
#include <unistd.h>
#include <dirent.h>
#include "log.h" // new zjx9083

std::string SambaTransfer::s_username;
// std::string SambaTransfer::s_wg="";
std::string SambaTransfer::s_password;

void SambaTransfer::static_authFn(const char *server, const char *share, char *wg, int wgmaxlen,
                char *un, int unmaxlen, char *pw, int pwmaxlen){
    // strncpy(un, s_username, unmaxlen - 1);
    strncpy(un, s_username.c_str(), unmaxlen - 1);
    strncpy(pw, s_password.c_str(), pwmaxlen - 1);
    // strncpy(wg, s_wg, wgmaxlen - 1);
}

int SambaTransfer::SetFileUrls(){
    return GetFileUrlsRecursive(downloadUrl);
}

int SambaTransfer::GetFileUrlsRecursive(std::string _url){
    if(_url[_url.size()-1] != '/'){
        _url += '/';
    }
    int dh = smbc_opendir(_url.c_str());
    if (dh < 0) {
         SLOGE("Failed to open directory:{}", _url.c_str());
        return -1;
    }
    // Call smbc_readdir in a loop to read all files in the folder
    struct smbc_dirent* dirent;
    while ((dirent = smbc_readdir(dh)) != nullptr) {
        // Ignore special directories "." and ".."
        if (strcmp(dirent->name, ".") == 0 || strcmp(dirent->name, "..") == 0) {
            continue;
        }
        // The full path to the build file
        std::string path = _url;
        path += dirent->name;
        // If it is a subdirectory, recursively process all files in the directory
        if (dirent->smbc_type == SMBC_DIR) {
            path += "/";
            int ret = GetFileUrlsRecursive(path);
            if(ret<0) {
                 SLOGE("Failed to use GetFileUrlsRecursive{}", path.c_str());
                return -1;
            }
        } else {
            //If it is a file, add its path to the vector
            struct stat st;
            smbc_stat(path.c_str(), &st);
            allFileUrls.push_back(std::pair<std::string, float>(path, st.st_size));
            allDownloadFileSize += st.st_size;
            if(fileSuffixes[0]=="all"){
                specificSuffixFileUrls.push_back(std::pair<std::string, float>(path, st.st_size));
                specificSuffixFileSize += st.st_size;
            }else{
                for(auto fileSuffix : fileSuffixes){
                    if(path.size()>fileSuffix.size() && path.substr(path.size()-fileSuffix.size(), fileSuffix.size()) == fileSuffix){
                        specificSuffixFileUrls.push_back(std::pair<std::string, float>(path, st.st_size));
                        specificSuffixFileSize += st.st_size;
                        break;
                    }
                }
            }
        }
    }
    // close directory handle
    smbc_closedir(dh);
    return 0;
}

int SambaTransfer::SetFilePaths(){
    return GetFilePathsRecursive(fileUploadPath);
}

int SambaTransfer::GetFilePathsRecursive(std::string _path){
    if(_path[_path.size()-1] != '/'){
        _path += '/';
    }
    DIR* dh = opendir(_path.c_str());
    if (dh < 0) {
         SLOGE("Failed to open directory:{}", _path.c_str());
        return -1;
    }
    // Call smbc_readdir in a loop to read all files in the folder
    struct dirent* dirent;
    while ((dirent = readdir(dh)) != nullptr) {
        // Ignore special directories "." and ".."
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }
        // The full path to the build file
        std::string path = _path;
        path += dirent->d_name;
        struct stat statBuf;
        if (stat(path.c_str(), &statBuf) < 0) {
             SLOGE("stat error");
            return -1;
        }
        // If it is a subdirectory, recursively process all files in the directory
        if (S_ISDIR(statBuf.st_mode)) {
            path += "/";
            int ret = GetFilePathsRecursive(path);
            if(ret<0) {
                 SLOGE("Failed to use GetFilePathsRecursive{}", path.c_str());
                return -1;
            }
        } else {
            //If it is a file, add its path to the vector
            struct stat st;
            stat(path.c_str(), &st);
            allFilePaths.push_back(std::pair<std::string, float>(path, st.st_size));
            allUploadFileSize += st.st_size;
        }
    }
    // close directory handle
    closedir(dh);
    return 0;
}

void SambaTransfer::PutFileUrls(){
    std::cout << "allFileUrls info:" << std::endl;
    std::cout << "allFileUrls Size:" << allDownloadFileSize /(1024*1024) << "MB" << std::endl;
    for(auto FileUrl: allFileUrls){
        std::cout << FileUrl.first << " " << FileUrl.second << "bytes" << std::endl;
    }

    std::cout << "specificSuffixFileUrls info:" << std::endl;
    std::cout << "specificSuffixFileUrls Size:" << specificSuffixFileSize/(1024*1024) << "MB" << std::endl;
    for(auto FileUrl: specificSuffixFileUrls){
        std::cout << FileUrl.first << " " << FileUrl.second << "bytes" << std::endl;
    }
}

void SambaTransfer::PutFilePaths(){
    std::cout << "allFilePaths info:" << std::endl;
    std::cout << "allFilePaths Size:" << allUploadFileSize /(1024*1024) << "MB" << std::endl;
    for(auto FilePath: allFilePaths){
        std::cout << FilePath.first << " " << FilePath.second << "bytes" << std::endl;
    }
}

// Create the folder path where the target file is remoted
void SambaTransfer::remoteMkdirRecursive(const char* path, int index) {
    if(strlen(path)-1 <= index) return;
    char* sep = strchr(const_cast<char*>(path + index), '/');
    if (sep != nullptr) {
        *sep = '\0';
        // struct stat st;
        // int ret = smbc_stat(path, &st);
        int ret = smbc_mkdir(path, 0755);
        if(ret<0)   SLOGE("Fail：smbc_mkdir{}, ret={}", path, ret);
        *sep = '/';
        remoteMkdirRecursive(path, sep-path+1);
    }
}

// Create the folder path where the target file is located
void SambaTransfer::locateMkdirRecursive(const char* path, int index) {
    if(strlen(path) < index) return;
    char* sep = strchr(const_cast<char*>(path + index), '/');
    if (sep != nullptr) {
        *sep = '\0';
        if (access(path, F_OK) == -1) {
            mkdir(path, 0755);
        }
        *sep = '/';
        locateMkdirRecursive(path, sep-path+1);
    }
}

int SambaTransfer::DownloadAll(){
    // Necessary variables to determine whether to initialize
    if(downloadUrl == ""){
         SLOGE("Fail：file download win downloadUrl not set");
        return -1;
    }
    struct stat st;
    int ret = smbc_stat(downloadUrl.c_str(), &st);
    if(ret < 0){
         SLOGE("Fail : smbc_stat{} , ret :{}",downloadUrl.c_str(), ret);
        return -2;
    }
    if(!S_ISDIR(st.st_mode)){
         SLOGE("Fail : dir downloadUrl{} is incorrect", downloadUrl.c_str());
        return -3;
    }
    if(fileDownloadPath == ""){
         SLOGE("Fail：file download qnx Path not set");
        return -4;
    }
    if(fileSuffixes.size() == 0){
         SLOGE("Fail：file suffixes not set");
        return -5;
    }
    allFileUrls.clear();
    specificSuffixFileUrls.clear();
    allDownloadFileSize = 0;
    specificSuffixFileSize = 0;
    SetFileUrls(); 

    char buffer[1024] = {0};
    for(auto fileUrlPair: specificSuffixFileUrls){
        bzero(buffer,1024);
        // Remote shared file absolute path
        std::string absoluteFileUrl = fileUrlPair.first;                                                       
        // Remote shared file relative path 
        std::string relativeFileUrl = absoluteFileUrl.substr(downloadUrl.size(), absoluteFileUrl.size()-downloadUrl.size());
        // Local file save path
        std::string fileDownloadUrl = fileDownloadPath + relativeFileUrl;
        locateMkdirRecursive(fileDownloadUrl.c_str(), 0);
        int fd;
        SLOGI("Download File:{}", fileDownloadUrl.c_str());
        if((fd = smbc_open(absoluteFileUrl.c_str(), O_RDONLY, 0777)) > 0){
            FILE *fp = fopen(fileDownloadUrl.c_str(), "w");
            if(fp == 0){
                 SLOGE("Error open qnx locate File url:{}", fileDownloadUrl.c_str());
                return -6;
            }
            int buflen = 0;
            while((buflen = smbc_read(fd,buffer,1024)) > 0){
                fwrite(buffer, 1, buflen, fp);
            }
            fclose(fp);
            smbc_close(fd);
            SLOGI("Success Download File:{}", fileDownloadUrl.c_str());
        }else{
             SLOGE("Fail Download File:{}", fileDownloadUrl.c_str());
            return -7;
        }
    }
    return 0;
}

int SambaTransfer::DownloadOne(){
    // Necessary variables to determine whether to initialize
    if(fileDownloadPath == ""){
         SLOGE("Fail：file download qnx Path not set");
        return -1;
    }
    if(downloadUrl == ""){
         SLOGE("Fail：file download win downloadUrl not set");
        return -2;
    }
    struct stat st;
    int ret = smbc_stat(downloadUrl.c_str(), &st);
    if(ret < 0){
         SLOGE("Fail : smbc_stat{} , ret :{}", downloadUrl.c_str(), ret);
        return -3;
    }
    if(!S_ISREG(st.st_mode)){
         SLOGE("Fail : file downloadUrl{} is incorrect", downloadUrl.c_str());
        return -4;
    }
    aDownloadFileSize = st.st_size;
    allFileUrls.clear();
    specificSuffixFileUrls.clear();
    allDownloadFileSize = 0;
    specificSuffixFileSize = 0;

    // char buffer[1024] = {0};
    char* buffer = (char*)malloc(1024*1024*10);
    int fd;
    SLOGI("Download File:{}", downloadUrl.c_str());
    std::string fileDownloadUrl;
    if((fd = smbc_open(downloadUrl.c_str(), O_RDONLY, 0777)) > 0){
        std::size_t pos = downloadUrl.find_last_of("/");
        if (pos != std::string::npos) fileDownloadUrl = downloadUrl.substr(pos + 1);
        else{
             SLOGE("Error Download File url:{}", downloadUrl.c_str());
            return -5;
        } 
        fileDownloadUrl = fileDownloadPath + fileDownloadUrl;
        locateMkdirRecursive(fileDownloadUrl.c_str(), 0);
        FILE *fp = fopen(fileDownloadUrl.c_str(), "w");
        int buflen = 0;
        while((buflen = smbc_read(fd,buffer,1024*1024*10)) > 0){
            fwrite(buffer, 1, buflen, fp);
        }
        if(buffer){
            free(buffer);
        }
        fclose(fp);
        smbc_close(fd);
        SLOGI("Success Download File:{}", fileDownloadUrl.c_str());
    }else{
         SLOGE("Fail Download File:{}", fileDownloadUrl.c_str());
        return -6;
    }
    return 0;
}

int SambaTransfer::UploadOne(){
    if(uploadUrl == ""){
         SLOGE("Fail：file upload win uploadUrl not set");
        return 1;
    }
    if(uploadUrl[uploadUrl.size()-1] != '/'){
        uploadUrl += '/';
    }
    // 上传的url第四个/之前的文件夹是不需要创建的本来就有
    int n = 0;
    for(int i=0; i<uploadUrl.size(); i++){
        if(uploadUrl[i]=='/'){
            n++;
        }
        if(n==4){
            remoteMkdirRecursive(uploadUrl.c_str(), i+1);
            break;
        }
    }
    struct stat st;
    int ret = smbc_stat(uploadUrl.c_str(), &st);
    if(ret < 0){
         SLOGE("Fail : smbc_stat{} , ret :{}",uploadUrl.c_str(), ret);
        return -2;
    }
    if(!S_ISDIR(st.st_mode)){
         SLOGE("Fail : dir uploadUrl{} is incorrect", uploadUrl.c_str());
        return -3;
    }
    if(fileUploadPath == ""){
         SLOGE("Fail：file upload qnx path not set");
        return -4;
    }
    ret = stat(fileUploadPath.c_str(), &st);
    if(ret < 0){
         SLOGE("Fail : stat{} , ret :{}",fileUploadPath.c_str(), ret);
        return -5;
    }
    if(!S_ISREG(st.st_mode)){
         SLOGE("Fail : qnx upload file path{} is incorrect", fileUploadPath.c_str());
        return -6;
    }
    std::string fileUploadUrl;
    std::size_t pos = fileUploadPath.find_last_of("/");
    if (pos != std::string::npos) fileUploadUrl = fileUploadPath.substr(pos + 1);
    else{
         SLOGE("pos: {}", pos);
         SLOGE("Error Download File uploadUrl:{}", uploadUrl.c_str());
        return -7;
    } 
    fileUploadUrl = uploadUrl + fileUploadUrl;
    int fd = open(fileUploadPath.c_str(), O_RDONLY);
    if(fd >= 0) {
        int fp = smbc_open(fileUploadUrl.c_str(), O_RDWR | O_CREAT, 0666);
        if(fp < 0){
             SLOGE("Fail : remote file{} open fail", fileUploadUrl.c_str());
            return -8;
        }
        else{
            char buffer[1024];
            ssize_t buflen;
            while((buflen = read(fd, buffer, 1024)) > 0) {
                smbc_write(fp, buffer, buflen);
            }
            smbc_close(fp);
            SLOGI("Success Download File: {} to remote{}", fileUploadPath.c_str(), fileUploadUrl.c_str());
        }
        close(fd);
    }else{
         SLOGE("Fail : locate file{} open fail", fileUploadPath.c_str());
        return -9;
    }
    return 0;

}

int SambaTransfer::UploadAll(){
    if(uploadUrl == ""){
         SLOGE("Fail：file upload win uploadUrl not set");
        return -1;
    }
    if(uploadUrl[uploadUrl.size()-1] != '/'){
        uploadUrl += '/';
    }
    // 上传的url第四个/之前的文件夹是不需要创建的本来就有
    int n = 0;
    for(int i=0; i<uploadUrl.size(); i++){
        if(uploadUrl[i]=='/'){
            n++;
        }
        if(n==4){
            remoteMkdirRecursive(uploadUrl.c_str(), i+1);
            break;
        }
    }
    struct stat st;
    int ret = smbc_stat(uploadUrl.c_str(), &st);
    if(ret < 0){
        fprintf(stderr, "Fail :  %s: %s\n", uploadUrl.c_str(), strerror(errno));
         SLOGE("Fail : smbc_stat{} , ret :{}",uploadUrl.c_str(),  ret);
        return -2;
    }
    if(!S_ISDIR(st.st_mode)){
         SLOGE("Fail : dir uploadUrl{} is incorrect", uploadUrl.c_str());
        return -3;
    }
    if(fileUploadPath == ""){
         SLOGE("Fail：file upload qnx path not set");
        return -4;
    }
    ret = stat(fileUploadPath.c_str(), &st);
    if(ret < 0){
         SLOGE("Fail : stat(fileUploadPath) , ret :{}", ret);
        return -5;
    }
    #if 1
    if(!S_ISDIR(st.st_mode)){
         SLOGE("Fail : qnx upload dir path: {} is incorrect", fileUploadPath.c_str());
        return -6;
    }
    #endif
    
    allFilePaths.clear();
    allUploadFileSize = 0;
    SetFilePaths(); 
    char buffer[1024] = {0};
    for(auto FilePath: allFilePaths){
        bzero(buffer,1024);
        // Remote shared file absolute path
        std::string absoluteFilePath = FilePath.first;                                                       
        // Remote shared file relative path 
        std::string relativeFilePath = absoluteFilePath.substr(fileUploadPath.size(), absoluteFilePath.size()-fileUploadPath.size());
        // Local file save path
        std::string fileUploadUrl = uploadUrl + relativeFilePath;
        // remoteMkdirRecursive(fileUploadUrl.c_str(), 0);
        SLOGI("Upload File:{}", fileUploadUrl.c_str());
        int fd = open(absoluteFilePath.c_str(), O_RDONLY);
        if(fd >= 0) {
            int fp = smbc_open(fileUploadUrl.c_str(), O_RDWR | O_CREAT, 0666);
            if(fp < 0){
                 SLOGE("Fail : remote file{} open fail", fileUploadUrl.c_str());
                return -7;
            }
            else{
                char buffer[1024];
                ssize_t buflen;
                while((buflen = read(fd, buffer, 1024)) > 0) {
                    smbc_write(fp, buffer, buflen);
                }
                smbc_close(fp);
                SLOGI("Success Upload File: {} to remote{}", absoluteFilePath.c_str(), fileUploadUrl.c_str());
            }
            close(fd);
        }else{
             SLOGE("Fail : locate file{} open fail", absoluteFilePath.c_str());
            return -8;
        }
    }
    return 0;
}

// int main(){
//     // SambaTransfer* sambaclient = new SambaTransfer("User", "wangcan", "Qwer1234");
//     // // download all
//     // sambaclient->SetUrl("smb://172.17.186.42/share");
//     // sambaclient->SetFileDownloadPath("download1");
//     // sambaclient->SetFileSuffixes(std::vector<std::string>{"all"});
//     // sambaclient->DownloadAll();
//     // std::cout<<std::endl;
//     // // download suffix
//     // sambaclient->SetFileDownloadPath("download2");
//     // sambaclient->SetFileSuffixes(std::vector<std::string>{".txt", ".jpg"});
//     // sambaclient->DownloadAll();
//     // std::cout<<std::endl;
//     // // download one
//     // sambaclient->SetUrl("smb://172.17.186.42/share/time.txt");
//     // sambaclient->SetFileDownloadPath("download3");
//     // sambaclient->DownloadOne();

//     // // upload one
//     // sambaclient->SetUrl("smb://172.17.186.42/share/upload"); // does not exist dir, will create
//     // sambaclient->SetfileUploadPath("./upload/test.txt");
//     // sambaclient->UploadOne();
//     // std::cout<<std::endl;
//     // sambaclient->SetUrl("smb://172.17.186.42/share");
//     // sambaclient->SetfileUploadPath("./upload/test.txt");
//     // sambaclient->UploadOne();
//     // std::cout<<std::endl;
//     // // upload all
//     // sambaclient->SetUrl("smb://172.17.186.42/share");
//     // sambaclient->SetfileUploadPath("./upload");
//     // sambaclient->UploadAll();
//     // std::cout<<std::endl;
//     // sambaclient->SetUrl("smb://172.17.186.42/share/upload");
//     // sambaclient->SetfileUploadPath("./upload");
//     // sambaclient->UploadAll();


//     SambaTransfer* sambaclient = new SambaTransfer("ARCSOFT-HZ", "xjf2613", "xjf.4776289c");
//     // // download all
//     // sambaclient->SetUrl("smb://172.17.11.202/objective_result");
//     // sambaclient->SetFileDownloadPath("download1");
//     // sambaclient->SetFileSuffixes(std::vector<std::string>{"all"});
//     // sambaclient->DownloadAll();
//     // std::cout<<std::endl;
//     // // download suffix
//     // sambaclient->SetFileDownloadPath("download2");
//     // sambaclient->SetFileSuffixes(std::vector<std::string>{".txt", ".jpg"});
//     // sambaclient->DownloadAll();
//     // std::cout<<std::endl;
//     // // download one
//     // sambaclient->SetUrl("smb://172.17.186.42/share/time.txt");
//     // sambaclient->SetFileDownloadPath("download3");
//     // sambaclient->DownloadOne();

//     // upload one
//     sambaclient->SetUrl("smb://172.17.11.202/objective_result"); // does not exist dir, will create
//     sambaclient->SetfileUploadPath("./upload/456.txt");
//     sambaclient->UploadOne();
//     // std::cout<<std::endl;
//     // sambaclient->SetUrl("smb://172.17.11.202/objective_resullt");
//     // sambaclient->SetfileUploadPath("./upload/test.txt");
//     // sambaclient->UploadOne();
//     std::cout<<std::endl;
//     // upload all
//     sambaclient->SetUrl("smb://172.17.11.202/objective_result/upload");
//     sambaclient->SetfileUploadPath("./upload");
//     sambaclient->UploadAll();
//     // std::cout<<std::endl;
//     // sambaclient->SetUrl("smb://172.17.11.202/objective_resullt/upload2");
//     // sambaclient->SetfileUploadPath("./upload2");
//     // sambaclient->UploadAll();
//     return 0;
// }