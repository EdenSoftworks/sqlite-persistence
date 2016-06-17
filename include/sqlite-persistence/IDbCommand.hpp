#ifndef _IDBCOMMAND_HPP_
    #define _IDBCOMMAND_HPP_

#pragma once
#include "IDisposable.hpp"
#include "ClassType.hpp"

#include "sqlite/sqlite3.h"

#include <string>

class IDbConnection;
class IDbQuery;
class IDbReader;

class IDbCommand : virtual IDisposable
{
    CLASS_TYPE(IDbCommand);

public:
    virtual ~IDbCommand(void) { }

	virtual void Cancel(void) = 0;

	virtual void ExecuteNonQuery(void) = 0;
	virtual IDbReader* const ExecuteReader(void) = 0;
	virtual std::string ExecuteScalar(void) = 0;

	virtual sqlite3_stmt* const Prepare(void) = 0;

    virtual IDbConnection* const Connection(void) = 0;

    virtual IDbQuery* const getQuery(void) = 0;
    virtual sqlite3_stmt* const getStmt(void) = 0;
    virtual const bool isPrepared(void) = 0;

    virtual const std::string getErr(void) = 0;

}; // < end interface.

#endif _IDBCOMMAND_HPP_