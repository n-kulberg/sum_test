#ifndef __kahan_sum_h
#define __kahan_sum_h

#include "abstract_sum.h"


template<class T>
class kahan_sum : public abstract_sum<T>
{
public:
	void operator+= (T x) override
	{
		volatile T	y = x - bias;
		volatile T	t = buffer + y;
		bias = t - buffer;
		bias -= y;
		buffer = t;
	}

	T	result() const override { return buffer; }

	void	reset() override { buffer = 0; bias = 0; }

private:
	volatile T	buffer = 0;
	volatile T	bias = 0;
};

#endif //__kahan_sum_h
