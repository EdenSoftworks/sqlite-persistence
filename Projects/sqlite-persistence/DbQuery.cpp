#pragma once
#include "DbQuery.hpp"

DbQuery::DbQuery(std::string _sqlQuery)
	: m_query(_sqlQuery)
{

}

DbQuery::~DbQuery(void) { }

const std::string DbQuery::Text(void) { return m_query; }