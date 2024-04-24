#include <iostream>
#include "errorcode.h"

// 定义一个错误工厂
class MyErrorFacility : public errfac {
public:
    MyErrorFacility() : errfac("MyErrorFacility") {}
    const int ERROR_CODE_SUCCESS = 0;
    const int ERROR_CODE_NULL_POINTER = 10;
    const int ERROR_CODE_INVALID_ARGUMENT = 20;
};

// 创建一个错误工厂实例
MyErrorFacility myFacility;

// 函数中可能会出现错误
erc myFunction(int* p, int n) {
    if (!p) {
        // 创建一个错误码为1（空指针）的错误实例并返回
        return erc(myFacility.ERROR_CODE_SUCCESS, ERROR_PRI_ERROR, &myFacility);
    }
    if (n <= 0) {
        // 创建一个错误码为2（无效参数）的错误实例并返回 
        return erc(myFacility.ERROR_CODE_INVALID_ARGUMENT, ERROR_PRI_WARNING, &myFacility);
    }
    return erc();
}

int myFunction2(int a, int b){
    if(a == b){
        erc(myFacility.ERROR_CODE_SUCCESS, ERROR_PRI_ERROR, &myFacility);
    }
    return a+b;
}


int main() {
    // 错误 if判断
    erc result1 =  myFunction(nullptr, 0);
    // 检查是否有错误发生
    if (result1) {
        // 如果发生错误，则将错误码记录到日志中
        result1.deactivate(); // 不再抛出错误，只记录日志
        std::cerr << "Error1: " << result1 << std::endl;
    }
    else {
        // 没有错误发生，继续执行
        std::cout << "Success!" << std::endl;
    }
    // 错误 try捕获
    try {
        int a = 1;
        int * p = &a;
        // 调用可能会出错的函数
        erc result2 =  myFunction(p, 0);
    }
    catch (erc& e) {
        // 捕获错误并记录日志
        e.deactivate(); // 防止重新抛出错误
        std::cerr << "Error2: " << e << std::endl;
    }
    try {
        int result3 =  myFunction2(1, 1);
    }
    catch (erc& e) {
        // 捕获错误并记录日志
        e.deactivate(); // 防止重新抛出错误
        std::cerr << "Error3: " << e << std::endl;
    }
    // 错误 不捕获
    // myFunction(nullptr, 0);
    return 0;
}
