#ifndef _IDISPOSABLE_HPP_
	#define _IDISPOSABLE_HPP_

#pragma once

class IDisposable
{
public:

    virtual ~IDisposable(void) { }

	virtual void Dispose(void) = 0;

}; // < end interface.

#endif _IDISPOSABLE_HPP_