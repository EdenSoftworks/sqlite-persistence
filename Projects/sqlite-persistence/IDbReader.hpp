#ifndef _IDBREADER_HPP_
	#define _IDBREADER_HPP_

#pragma once
#include "IDisposable.hpp"

#include "ClassType.hpp"

#include <string>
#include <vector>

class IDbReader : virtual IDisposable
{
    CLASS_TYPE(IDbReader);

public:

    virtual ~IDbReader(void) { };

    virtual bool Read(void) = 0;

    virtual const std::vector<std::string> GetRow(void) = 0;

}; // < end interface.

#endif _IDBREADER_HPP_