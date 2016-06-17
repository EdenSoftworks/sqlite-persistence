#pragma once
#include "DbCommand.hpp"

#include "DbConnection.hpp"
#include "DbReader.hpp"
#include "IDbConnection.hpp"
#include "IDbReader.hpp"
#include "IDbQuery.hpp"
#include "IDbTransaction.hpp"
#include "Sqlite3Helper.hpp"

#include "sqlite/sqlite3.h"

#include <iostream>
#include <cassert>
#include <string>

DbCommand::DbCommand(IDbQuery* const _pQuery, IDbConnection* const _pConnection, IDbTransaction* const _pTransaction)
    : m_pQuery(_pQuery), m_pConnection(_pConnection), m_pTransaction(_pTransaction), m_pStatement(nullptr)
    , m_bPrepared(false) { }

DbCommand::~DbCommand(void)
{
	Dispose();
}

void DbCommand::Dispose(void)
{
    if (this->m_pStatement != nullptr)
    {
        // < Just in case.
        sqlite3_finalize(this->m_pStatement);
        this->m_pStatement = nullptr;

        this->m_bPrepared = false;
    }
}

IDbConnection* const DbCommand::Connection(void) { return this->m_pConnection; }

IDbQuery* const DbCommand::getQuery(void) { return this->m_pQuery; }

sqlite3_stmt* const DbCommand::getStmt(void) { return this->m_pStatement; }

const bool DbCommand::isPrepared(void) { return this->m_bPrepared; }

const std::string DbCommand::getErr(void) { return this->m_pConnection->ErrorMessage(); }

void DbCommand::Cancel(void)
{
	if (!m_pConnection->HasAnyConnectionState(CONNECTION_CLOSING | CONNECTION_CLOSED))
	{
		sqlite3_interrupt(m_pConnection->Database());
	}
}

void DbCommand::ExecuteNonQuery(void)
{
    if (!this->m_bPrepared) { this->Prepare(); }

    sqlite3_exec(this->m_pConnection->Database(), this->m_pQuery->Text().c_str(), 0, 0, nullptr);   // < Probably should do something about that
                                                                                                    // * given err nullptr.
}

IDbReader* const DbCommand::ExecuteReader(void)
{
    if (!this->m_bPrepared) { this->Prepare(); }

    return new DbReader(this);
}

std::string DbCommand::ExecuteScalar(void)
{
    if (!this->m_bPrepared) { this->Prepare(); }

    auto reader = this->ExecuteReader();

    std::string res;
    res = (reader->Read() && !reader->GetRow().empty()) ? reader->GetRow()[0] : "";

    delete reader;
    reader = nullptr;

    return res;
}

sqlite3_stmt* const  DbCommand::Prepare(void)
{
    if (this->m_pConnection->HasConnectionState(CONNECTION_CLOSED)) { this->m_pConnection->Open(); }

    // < No need to prepare the statement a second time.
    if (this->m_bPrepared) { return this->m_pStatement; }

    auto res = sqlite3_prepare_v2((m_pConnection->Database()), m_pQuery->Text().c_str(), -1, &this->m_pStatement, 0);
    if (res != SQLITE_OK)
    {
        auto err = this->m_pConnection->ErrorMessage();
        if (err != "not an error") std::cerr << " " << err << std::endl;

        assert(res != SQLITE_OK);
    }


    this->m_bPrepared = true;

    return this->m_pStatement;
}