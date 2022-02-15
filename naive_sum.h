#ifndef __naive_sum_h
#define __naive_sum_h

#include "abstract_sum.h"


template<class T>
class naive_sum : public abstract_sum<T>
{
public:
	void operator+= (T x) override
	{
		buffer += x;
	}

	T	result() const override { return buffer; }

	void	reset() { buffer = 0; }

private:
	T	buffer = 0;
	T	bias = 0;
};


#endif //__naive_sum_h
