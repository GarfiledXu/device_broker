#ifndef SAMBA_TRANSFER_
#define SAMBA_TRANSFER_
#include <iostream>
#include <vector>
#include <string.h>
#include <regex>
#include <libsmbclient.h>
// #include "component-all.hpp"
#include "log.h" // new zjx9083


class SambaTransfer{
public:
    SambaTransfer(std::string username, std::string password){
        status = 0;
        s_username = username;
        s_password = password;
        SLOGI("Samba init: username:{},password:{}" , username.c_str(), password.c_str());
        allDownloadFileSize = 0;
        aDownloadFileSize = 0;
        allUploadFileSize = 0;
        aUploadFileSize = 0;
        int err = smbc_init(static_authFn, 0);
        if(err < 0){
            status = -1;
            SLOGE("smbc_init error");
        }
        fileDownloadPath = "smb://172.17.11.202/objective_result";
    }
    
    int SetDownloadUrl(std::string url){ 
        if(!isIPBasedSMBPath(url)){
            SLOGE("The samba DownloadUrl {} is not in the correct format.", url.c_str());
            SLOGE("the sambs correct format: smb://ip//xxx/xxx");
            return -1;
        }
        this->downloadUrl = url;
        SLOGI("DownloadUrl init:{}",url.c_str());
        return 0;
    };
    int SetUploadUrl(std::string url){ 
        if(!isIPBasedSMBPath(url)){
            SLOGE("The samba UploadUrl {} is not in the correct format.", url.c_str());
            SLOGE("the sambs correct format: smb://ip//xxx/xxx");
            return -1;
        }
        this->uploadUrl = url;
        SLOGI("UploadUrl init:{}",url.c_str());
        return 0;
    };
    void SetFileDownloadPath(std::string fileDownloadPath) { 
        //  SLOGI("123131 %d", fileDownloadPath.size()-1);
        // if(fileDownloadPath[fileDownloadPath.size()-1] != '/'){
        //     fileDownloadPath += '/';
        // }
        this->fileDownloadPath = fileDownloadPath +'/';
        // SLOGI("123131");
    }
    void SetFileSuffixes(std::vector<std::string> fileSuffixes) { this->fileSuffixes = fileSuffixes;}
    // pre operation: setFileSuffixes() and SetFileDownloadPath() and SetUrl()
    int SetFileUrls();
    
    // if user relative path must start with ./
    void SetfileUploadPath(std::string fileUploadPath){ this->fileUploadPath = fileUploadPath;}
    //pre operation: SetfileUploadPath() and SetUrl()
    int SetFilePaths(); 
    
    /**
     * download all/suffix file under the remote url to loacl path
     * pre operation: SetDownloadUrl() SetFileDownloadPath() SetFileSuffixes() 
     * 
     * exp: download all files
     *      SambaTransfer* sambaclient = new SambaTransfer("ARCSOFT-HZ", "xjf2613", "xjf.4776289c");
     *      sambaclient->SetDownloadUrl("smb://172.17.11.202/objective_result");
     *      sambaclient->SetFileDownloadPath("download1");
     *      sambaclient->SetFileSuffixes(std::vector<std::string>{"all"});
     *      sambaclient->DownloadAll();
     * 
     * exp: download specify suffix files
     *      ...
     *      sambaclient->SetFileSuffixes(std::vector<std::string>{".txt", ".jpg"});
     *      sambaclient->DownloadAll();
    */
    int DownloadAll(); 
    /**
     * download the remote url file to local path
     * pre operation: SetUrl() SetFileDownloadPath() 
     * 
     * exp: 
     *      SambaTransfer* sambaclient = new SambaTransfer("ARCSOFT-HZ", "xjf2613", "xjf.4776289c");
     *      sambaclient->SetUrl("smb://172.17.186.42/share/time.txt");
     *      sambaclient->SetFileDownloadPath("download1");
     *      sambaclient->DownloadOne();
    */
    int DownloadOne(); 

    /**
     * upload all file under the local path to remote url
     * pre operation: SetUrl() and SetfileUploadPath()
     * 
     * exp:
     *      sambaclient->SetUrl("smb://172.17.11.202/objective_result/upload");
     *      sambaclient->SetfileUploadPath("./upload");
     *      sambaclient->UploadAll();
     */ 
    int UploadAll();
    /**
     * upload local path file to remote url
     * pre operation: SetUrl() and SetfileUploadPath()
     * 
     * exp:
     *      sambaclient->SetUrl("smb://172.17.11.202/objective_result/upload");
     *      sambaclient->SetfileUploadPath("./upload/test.txt");
     *      sambaclient->UploadOne();
     */ 
    int UploadOne();

    // Recursively traverse remote url, init allFileUrls and specificSuffixFileUrls
    int GetFileUrlsRecursive(std::string path); 
    // Recursively traverse loacte path, init allFilePaths
    int GetFilePathsRecursive(std::string path); 
    // To testing : output the content of allFileUrls and specificSuffixFileUrls
    void PutFileUrls(); 
    // To testing : output the content of allFilePaths
    void PutFilePaths();  
    // locate mkdir 
    void locateMkdirRecursive(const char* path, int index); 
    // remote mkdir
    void remoteMkdirRecursive(const char* path, int index);

    static void static_authFn(const char *server, const char *share, char *wg, int wgmaxlen,
            char *wn, int unmaxlen, char *pw, int pwmaxlen);
    
    int Status(){return status;}

    bool isIPBasedSMBPath(const std::string& path) {
        std::regex pattern("smb://([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)/.*");
        return std::regex_match(path, pattern);
    }
    ~SambaTransfer(){}

private:
    std::mutex mutex_;

    static std::string s_username;
    static std::string s_password;
    // remote
    // std::string url;
    std::string downloadUrl;
    std::string uploadUrl;

    // purpose to download, remote file download to local path
    std::string fileDownloadPath;
    // all file url under the remote url 
    std::vector<std::pair<std::string, int>> allFileUrls;
    // all download file size
    int allDownloadFileSize;
    // specific suffic file url under the remote url 
    std::vector<std::pair<std::string, int>> specificSuffixFileUrls;
    // all download specific suffic file size
    int specificSuffixFileSize;
    // file suffic vec
    std::vector<std::string> fileSuffixes;
    // single download file size
    int aDownloadFileSize;

    // purpose to upload, local path upload to remote url
    std::string fileUploadPath;
    // all upload file size
    int allUploadFileSize;
    // all file path under the local path 
    std::vector<std::pair<std::string, int>> allFilePaths;
    // single upload file size
    int aUploadFileSize;

    int status;
};

class SafeSambaTrasfer{
public:
    SafeSambaTrasfer(std::string username, std::string pwd):smb_(username, pwd){}
   
    int DownloadOne(std::string url, std::string path){
        std::lock_guard<std::mutex> lock(mutex_);
        smb_.SetDownloadUrl(url);
        smb_.SetFileDownloadPath(path);
        return smb_.DownloadOne();
    }
   
    int UploadAll(std::string url, std::string file_url){
        std::lock_guard<std::mutex> lock(mutex_);
        smb_.SetUploadUrl(url);
        smb_.SetfileUploadPath(file_url);
        return smb_.UploadAll();
    }
    ~SafeSambaTrasfer(){
        SLOGI("delete SafeSamba");
    }
private:
    std::mutex mutex_;
    SambaTransfer smb_;
};

#endif
