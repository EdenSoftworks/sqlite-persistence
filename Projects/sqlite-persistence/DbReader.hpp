#ifndef _DBREADER_HPP_
	#define _DBREADER_HPP_

#pragma once
#include "IDbReader.hpp"

#include "ClassType.hpp"
#include "IDbCommand.hpp"

#include "sqlite/sqlite3.h"

#include <string>
#include <vector>

class DbReader : public IDbReader, public Disposable
{
    CLASS_TYPE(DbReader);

public:

    explicit DbReader(IDbCommand* const _pCommand);
    ~DbReader(void);

    void Dispose(void);

    bool Read(void);

    const std::vector<std::string> GetRow(void);

private:

    IDbCommand* const m_pCommand;

    std::vector<std::string> m_row;

    int m_nColumns;

}; // < end class.

#endif _DBREADER_HPP_