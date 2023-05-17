#pragma once 

#include "statistics.h"
#include <vector>
#include <string>


class Perc : public IStatistics {
public:
	Perc(int perc) : m_selection{} { set_percentage(perc); }  // set percentile value in constructor

    void set_percentage(int perc) { m_perc = perc; }          // set percentile value

	void update(double next) override {
        m_selection.push_back(next);
	}

	double eval() const override;
	const char * name() const override; 


private:
	std::vector<double> m_selection;     // vector to store values
    int m_perc;                          // percentile value
};

