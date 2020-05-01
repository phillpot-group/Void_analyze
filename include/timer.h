#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string_view>

class timer
{
public:
	timer(std::ostream &output, const std::string_view &s = "");
	void span() const;
	~timer();

private:
	// Static member : store the info that how many timer currently running
	inline static size_t count_total = 0;

	// private members
	std::ostream &os;
	std::chrono::steady_clock::time_point start;
	std::string_view message;
	size_t count_instance;

	// private member functions
	void indention() const;
};

inline timer::timer(std::ostream &output, const std::string_view &s) : os(output), start(std::chrono::steady_clock::now()), message(s), count_instance(count_total++)
{
	indention();
	os << "Timer: " << message << " begins..." << std::endl;
}

inline void timer::span() const
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	indention();
	os << "Timer: " << message << " costs ";
	os << time_span.count() << "ms" << std::endl;
}

inline timer::~timer()
{
	--count_total;
}

inline void timer::indention() const
{
	for (size_t i = 0; i != count_instance; ++i)
	{
		os << "\t";
	}
}
