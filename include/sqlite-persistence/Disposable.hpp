#ifndef _DISPOSABLE_HPP_
	#define _DISPOSABLE_HPP_

#pragma once
#include "IDisposable.hpp"

class Disposable : virtual IDisposable
{
public:

    ~Disposable(void) { }

	void Dispose(void) { }

}; // < end class.

#endif _DISPOSABLE_HPP_