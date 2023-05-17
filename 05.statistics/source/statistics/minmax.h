#pragma once 

#include "statistics.h"
#include <limits>


class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {}    // set maximum possible value as start

	void update(double next) override {    // if new number less than previus - replace value
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override { return m_min; }
	const char * name() const override { return "min"; }

private:
	double m_min;
};


class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::lowest()} {}  // set minimum possible value as start

	void update(double next) override {   // if new number bigger than previus - replace value
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override { return m_max; }
	const char * name() const override { return "max"; }

private:
	double m_max;
};