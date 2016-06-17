#ifndef _SQLITE3_HELPER_HPP_
    #define _SQLITE3_HELPER_HPP_

#pragma once

#include "sqlite/sqlite3.h"

#include <iostream>
#include <string>

static int c_callback(void* param, int argc, char** argv, char** azColName)
{
    unsigned index = 0;
    while (index < argc)
    {
        std::cerr << azColName[index] << "=" << argv[index] ? argv[index] : "NULL \n";

        ++index;
    }

    return 0;
}

static inline bool TableExists(sqlite3* _pDb, const std::string& _cTableName)
{
    std::string errMsg;

    sqlite3_stmt* pStmt;
    std::string query =
        "SELECT 1"
        " FROM sqlite_master"
        " WHERE type='table'"
        "  AND name=?;";

    auto res = sqlite3_prepare_v2(_pDb, query.c_str(), -1, &pStmt, nullptr);
    if (res != SQLITE_OK) { throw std::string(sqlite3_errmsg(_pDb)); }

    res = sqlite3_bind_text(pStmt, 1, _cTableName.c_str(), -1, SQLITE_TRANSIENT);
    if (res != SQLITE_OK)
    {
        errMsg = std::string(sqlite3_errmsg(_pDb));
        sqlite3_finalize(pStmt);
        throw errMsg;
    }

    res = sqlite3_step(pStmt);
    if (res != SQLITE_ROW && res != SQLITE_DONE)
    {
        errMsg = std::string(sqlite3_errmsg(_pDb));
        sqlite3_finalize(pStmt);
        throw errMsg;
    }

    if (res == SQLITE_DONE)
    {
        errMsg = "Table not found";
        sqlite3_finalize(pStmt);
        //throw errMsg;
        return false;
    }

    sqlite3_finalize(pStmt);
    return true;
}

#endif _SQLITE3_HELPER_HPP_
