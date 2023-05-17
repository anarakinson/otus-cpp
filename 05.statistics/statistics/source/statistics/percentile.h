#pragma once 

#include "statistics.h"
#include <vector>
#include <string>


class Perc : public IStatistics {
public:
	Perc(int perc) : m_selection{} { set_percentage(perc); }

    void set_percentage(int perc) { m_perc = perc; }

	void update(double next) override {
        m_selection.push_back(next);
	}

	double eval() const override;
	const char * name() const override; 


private:
	std::vector<double> m_selection;
    int m_perc;
};

