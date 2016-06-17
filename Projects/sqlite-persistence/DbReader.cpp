#pragma once
#include "DbReader.hpp"

#include "IDbConnection.hpp"

#include "sqlite/sqlite3.h"

#include <iostream>
#include <string>
#include <vector>

DbReader::DbReader(IDbCommand* const _pCommand)
    : m_pCommand(_pCommand), m_nColumns(sqlite3_column_count(_pCommand->getStmt()))
{
}

DbReader::~DbReader(void)
{
    Dispose();
}

void DbReader::Dispose(void)
{

}

const std::vector<std::string> DbReader::GetRow(void) { return m_row; }

bool DbReader::Read(void)
{
    std::string errMsg;

    auto res = sqlite3_step(this->m_pCommand->getStmt());
    if (res != SQLITE_ROW && res != SQLITE_DONE)
    {
        auto err = m_pCommand->Connection()->ErrorMessage();
        if (err != "not an error")
        {
            errMsg = err;
            sqlite3_finalize(this->m_pCommand->getStmt());
            throw errMsg;
        }

        sqlite3_finalize(this->m_pCommand->getStmt());

        // < I am unsure if it is possible to get here.
        return false;
    }

    if (res == SQLITE_DONE || this->m_nColumns <= 0)
    {
        // < Nothing to report.
        sqlite3_finalize(this->m_pCommand->getStmt());
        return false;
    }

    auto index = 0;
    while (index < this->m_nColumns)
    {
        std::string val;
        auto ptr = (char*)sqlite3_column_text(this->m_pCommand->getStmt(), index);

        if (ptr) { val = ptr; }

        this->m_row.push_back(val);
        ++index;
    }

    return true;
}