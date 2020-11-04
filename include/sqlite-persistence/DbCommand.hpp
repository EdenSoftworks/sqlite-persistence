#ifndef _DBCOMMAND_HPP_
    #define _DBCOMMAND_HPP_

#pragma once
#include "ClassType.hpp"

#include "sqlite/sqlite3.h"

#include <string>

class IDbConnection;
class IDbQuery;
class IDbTransaction;
template <typename T> class DbReader;

class DbCommand
{
    CLASS_TYPE(DbCommand);

public:

	DbCommand(IDbQuery* const _pQuery, IDbConnection* const _pConnection, IDbTransaction* const _pTransaction);
	virtual ~DbCommand(void);

	void Cancel(void);

	void ExecuteNonQuery(void);
	IDbReader* const ExecuteReader(void);
	std::string ExecuteScalar(void);

	sqlite3_stmt* const Prepare(void);

    IDbConnection* const Connection(void);

    IDbQuery* const getQuery(void);
    sqlite3_stmt* const getStmt(void);
    const bool isPrepared(void);
    const std::string getErr(void);

private:

	IDbConnection* const m_pConnection;

	IDbQuery* const m_pQuery;

	IDbTransaction* const m_pTransaction;

	sqlite3_stmt* m_pStatement;

    bool m_bPrepared;

}; // < end class.

#endif _DBCOMMAND_HPP_