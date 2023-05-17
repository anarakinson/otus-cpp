#pragma once 

#include "statistics.h"
#include <vector>



class Mean : public IStatistics {
public:
	Mean() : m_selection{} {}

	void update(double next) override {
        m_selection.push_back(next);
	}

	double compute_mean() const;
	double eval() const override { return compute_mean(); }
	const char * name() const override { return "mean"; }

protected:
	std::vector<double> m_selection;
};


class Sigma : public Mean {
public:
	Sigma() {}

	double eval() const override;
	const char * name() const override { return "std"; }
};

