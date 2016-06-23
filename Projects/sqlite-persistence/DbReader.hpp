#ifndef _DBREADER_HPP_
	#define _DBREADER_HPP_

#pragma once
#include "ClassType.hpp"
#include "DbCommand.hpp"

#include "sqlite/sqlite3.h"

#include <functional>
#include <string>
#include <vector>

template <typename T>
class DbReader
{
    CLASS_TYPE(DbReader);

public:

    explicit DbReader(DbCommand* const _pCommand);
    ~DbReader(void);

    bool Read(std::function<bool(DbReader<T>*, sqlite3_stmt*, T&)> _func);

    const unsigned long Columns(void);
    const T Result(void);

protected:

    bool Prepare(void);

private:

    DbCommand* const m_pCommand;

    T m_result;

    int m_nColumns;

}; // < end class.

#endif _DBREADER_HPP_