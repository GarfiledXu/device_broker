#ifndef SQLITE_H_
#define SQLITE_H_
#include<iostream>
#include<vector>
#include "sqlite3.h"

class Sqlite{
public:
    Sqlite(std::string dbFileName = "example.db");
    int connection();
    // exe sql return wether success
    int CUD(std::string);                   
    // exe sql have return result (code not test)
    std::vector<std::string> R(std::string);
    int state() {return state_;} 
    // show database content, (fixed db format)
    int show();                            
    ~Sqlite();
private:
    // database file name
    std::string dbFileName;
    // database connect object                  
    sqlite3* db;
    // connect to database whether success                             
    int state_;                             
};

#endif