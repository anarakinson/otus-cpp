#pragma once 

#include "statistics.h"
#include <vector>



class Mean : public IStatistics {
public:
	Mean() {}

	void update(double next) override {  // store new values in vector
        m_sum += next;
		++counter;
	}

	double compute_mean() const;         // compute mean
	double eval() const override { return compute_mean(); }  // return mean
	const char * name() const override { return "mean"; }

     // vector to store values

private:
	unsigned long counter = 0;
	double m_sum = 0;

friend class Sigma;
};


class Sigma : public Mean {
public:
	Sigma() : m_selection{} {}	
	
	void update(double next) override {  // store new values in vector
	    m_selection.push_back(next);
        m_sum += next;
		++counter;
	}

	double eval() const override;
	const char * name() const override { return "std"; }

private:
	std::vector<double> m_selection;
};

