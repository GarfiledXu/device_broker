#ifndef ERROR_CORE_HPP
#define ERROR_CORE_HPP

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<mutex>
using namespace std;

class errorcode {
private:
    std::mutex mutex_;
protected:
    int errClsCode;
public:
    static vector<string> errorClassStrVec;
    
    errorcode(string errorClass = "") {
        if(errorClass=="") errClsCode = 0;
        auto it = find(errorClassStrVec.begin(), errorClassStrVec.end(), errorClass);
        if (it == errorClassStrVec.end()) {
            std::unique_lock<std::mutex> lock(mutex_);
            errorClassStrVec.push_back(errorClass);
            errClsCode = errorClassStrVec.size()-1;
        } else {
            errClsCode = it - errorClassStrVec.begin();
        }
    };
    virtual ~errorcode() {}
    virtual operator int() = 0;
    virtual operator string() = 0;
};

#define ERROR_CLASS(className) \
    class className: public errorcode { \
    public:\
        className(string errStr): errorcode(#className) {\
            if (find(errorStrVec.begin(), errorStrVec.end(), errStr) == errorStrVec.end()) {\
                std::unique_lock<std::mutex> lock(mutex_);\
                errorStrVec.push_back(errStr);\
                errCode = errorStrVec.size()-1;\
            }\
        }\
        className(int errorindex): errorcode(#className) {\
            if (errorindex >= errorStrVec.size() || errorindex < 0) {\
                cout << "no have error" << endl;\
                return;\
            } else {\
                errCode = errorindex;\
            }\
        }\
        operator int() {\
            return errClsCode*100 + errCode;\
        }\
        operator string() {\
            return errorStrVec[errCode];\
        }\
    protected:\
        static vector<string> errorStrVec;\
        int errCode;\
        std::mutex mutex_;\
    };

ERROR_CLASS(errorTest)

#define Parser(code, res) \
    int errClsCode = (code - code%100)/100;\
    int errCode = code%100;\
    string errorClassStr = errorcode::errorClassStrVec[errClsCode];\
    errorcode* objName = nullptr; \
    if (errorClassStr == "errorTest") { \
        objName = new errorTest(errCode); \
        res = (string)*objName; \
    }else{\
        res = "praser not have errcode";\
    }\


#endif