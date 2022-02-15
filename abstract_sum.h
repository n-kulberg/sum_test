#ifndef __abstract_sum_h
#define __abstract_sum_h

template<class T>
class abstract_sum
{
public:
	virtual void	reset() = 0;
	virtual void	operator+=(T) = 0;
	virtual T	result() const = 0;
};


#endif //__abstract_sum_h
