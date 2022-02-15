// distributed_sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>

#include "naive_sum.h"
#include "kahan_sum.h"
#include "distributed_sum.h"

#ifdef _MSC_VER
#pragma warning( disable : 4305 4244)//ignore precision warning 'double-to-float'
#endif


template<class T1, class T2>
void	elementary_test(const std::vector<T1>& data, abstract_sum<T2> &sum, std::string title)
{
	sum.reset();
	for (auto& x : data)
	{
		sum += x;
	}

	std::cout << title << "\t=\t" << sum.result() << std::endl;
}

template<class F>
void run_all_tests()
{
	std::initializer_list<double> ranges = { 1e-32, 1e-24, 1e-16, 1e-12, 1e-8, 1e-4, 1, 1e4, 1e8, 1e12, 1e16, 1e24, 1e32 };
	distributed_sum<F> ds{ranges};
	kahan_sum<F>	ks;
	naive_sum<F>	ns;
	distributed_sum<double>		ps{ranges};

	F	normal  {1.1111111111111};
	F	big {1e6};
	F	huge {1e15};


	auto	run_tests = [&ds, &ns, &ks, &ps](const std::vector<F>& data)
	{
		std::cout << std::endl << "data = {";
		for (auto& x : data)
			std::cout << x << ", ";

		std::cout << "}" << std::endl;

		elementary_test<F>(data, ns, "naive");
		elementary_test(data, ks, "kahan");
		elementary_test(data, ds, "distributed");
		elementary_test(data, ps, "precise");
	};

	run_tests({ 100, normal,  2*normal});	 
	std::cout << "(no difference)\n";

	run_tests({ big, normal,  2*normal });
	std::cout << "(kahan and distributed work equally, naive loses digits if F=float)\n";

	run_tests({ big, normal, -big });
	std::cout << "(naive and kahan lose digits, distributed works well)\n";

	run_tests({ huge, normal, -huge });
	std::cout << "(kahan and naive lose digits if F=double or float, distributed works well)\n";
}

int main()
{
	const auto digits = std::numeric_limits<double>::digits10;
	std::cout << std::setprecision(digits);

	std::cout << "Running tests for float\n";
	run_all_tests<float>();
	
	std::cout << "\nRunning tests for double\n";
	run_all_tests<double>();
	return 0;
}
