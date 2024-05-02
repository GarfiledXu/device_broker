#include "sqlite.h"
#include "component-all.hpp"
#include "log.h" // new zjx9083
// int32_t LOG_LEVEL_MASK = EROR | VEBO | PRINT | INFO | DBUG | COLOR | EXTR;
Sqlite::Sqlite(std::string dbFileName):dbFileName(dbFileName){
    FILE *fp;
    fp = fopen(dbFileName.c_str(), "a+");
    if (fp == NULL) {
        SLOGE( "Cannot create/open {}", dbFileName.c_str());
        state_ = -1;
        return;
    }
    fclose(fp);
    state_ = connection();
}

int Sqlite::connection(){
    if(state_==-1) return -1;
    int rc = sqlite3_open(dbFileName.c_str(), &db);
    if (rc != SQLITE_OK) {
        SLOGE( "Cannot open database: {}", sqlite3_errmsg(db));
        state_ = -2;
        return -2;
    }
    state_ = 0;
    SLOGI( "open database success: {}", dbFileName.c_str());
    return rc;
}

// CURD中的CUD
int Sqlite::CUD(std::string sql){
    if(state_) return -1;
    char* errmsg = 0;
    SLOGI( "exec CUD sql: {}", sql.c_str());
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        if (errmsg != NULL) {
            SLOGE("Cannot exec CUD sql: {}", errmsg);
            sqlite3_free(errmsg);
        } else {
            SLOGE("Cannot exec CUD sql: unknown error");
        }
        return -2;
    }
    SLOGI("exec CUD sql success");
    return 0;
}

// 没测试 CURD中的R
std::vector<std::string> Sqlite::R(std::string sql){
    std::vector<std::string> row;
    sqlite3_stmt *stmt;
    SLOGI( "exec R sql: {}", sql.c_str());
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        SLOGE("Error preparing statement: {}", sqlite3_errmsg(db));
    }
    rc = sqlite3_step(stmt);
    // if (rc != SQLITE_OK) {
    //     SLOGE("Cannot exec R sql : {}", sqlite3_errmsg(db));
    // }
    // else {
        std::string s = "";
        int num_cols = sqlite3_column_count(stmt);
        for (int i = 0; i < num_cols; i++) {
            const char *val = (const char *) sqlite3_column_text(stmt, i);
            if (val) {
                s += val;
                row.push_back(val);
            } else {
                s += " ";
                row.push_back("");
            }
            if(i!=num_cols-1)s += "||";
        }
        SLOGI("exec R sql success: {}", s.c_str());
    // }
    sqlite3_finalize(stmt);
    return row;
}

// 特例化数据库格式
int Sqlite::show(){
    if(state_) return -1;
    // 准备 SQL 语句和结果集
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM message";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        SLOGE("Cannot exec SELECT * FROM message : {}", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -3;
    }

    SLOGI("SELECT * FROM message, result [time, msg, res, success]: ");
    // 逐行读取结果集
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // SLOGI("{} {} {}", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));
        const char* time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* msg = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* res = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int success = sqlite3_column_int(stmt, 3);
        
        SLOGI("|| {} | {} | {} | {} ||", time, msg, res, success);
    }

    // 释放资源并关闭连接
    sqlite3_finalize(stmt);
    return 0;
}

Sqlite::~Sqlite(){
    sqlite3_close(db);
}