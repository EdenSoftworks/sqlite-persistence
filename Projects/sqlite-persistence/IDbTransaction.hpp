#ifndef _IDBTRANSACTION_HPP_
	#define _IDBTRANSACTION_HPP_

#pragma once
#include "IDisposable.hpp"

#include "ClassType.hpp"

#include <string>

class IDbTransaction : virtual IDisposable
{
    CLASS_TYPE(IDbTransaction);

public:

    virtual ~IDbTransaction(void) { };

	virtual void Begin(std::string _trans = "") = 0;

	virtual void Commit(std::string _trans = "") = 0;

	virtual void Dispose(void) = 0;

	virtual void Rollback(std::string _trans = "") = 0;

}; // < end interface.

#endif _IDBTRANSACTION_HPP_
