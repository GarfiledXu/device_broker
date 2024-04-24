#include<errorcode.hpp>
/** 
 * add new error:
 * errorcode.hpp
 * - ERROR_CLASS(errorTest)
 * - Parser(code, res) 
 *      if (errorClassStr == "errorAdd") { 
 *          objName = new errorAdd(errCode); 
 *          ret = (string)*objName; 
 *       }
 * errorcode.cpp
 * - vector<string> errorTest::errorStrVec = {"success"};
 *
 * 
 * use err example:
 * errorcode* ret = new errorTest("error content");
 * int code = (int)*ret;
 * string str = (string)*ret;
 * Parser(code, str);
 */

vector<string> errorcode::errorClassStrVec = {"success"};
vector<string> errorTest::errorStrVec = {"success"};

// vector<string> errorcode::errorClassStrVec = {"success", "errorTest"};
// vector<string> errorTest::errorStrVec = {"success","err1","err2"};
// err1  101
// XX XX 101 == errorTest::123
// errorcode::iter errorTest::iter