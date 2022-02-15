#ifndef __distributed_sum_h
#define __distributed_sum_h

#include "abstract_sum.h"

#include <vector>
#include <set>

template<class T>
class distributed_sum : public abstract_sum<T>
{
public:
	distributed_sum(const std::initializer_list<double>& in_thresholds)
	{
		for (const auto& t : in_thresholds)
			m_thresholds.insert(fabs(t));
		m_buffers.resize(m_thresholds.size(), 0);
	}

	void operator+= (T x) override
	{
		auto b = m_buffers.begin();
		for (auto& t : m_thresholds)
		{
			if (fabs(x) < t)
			{
				*b += x;
				break;
			}
			b++;
		}
		if (b == m_buffers.end())
			m_buffers.back() += x;
	}

	T result() const override
	{
		T r{ 0 };
		for (const auto& b : m_buffers)
			r += b;
		return r;
	}

	void	reset() override { std::fill(m_buffers.begin(), m_buffers.end(), 0); }

private:
	std::vector<T> m_buffers;
	std::set<T> m_thresholds;
};


#endif //__distributed_sum_h
