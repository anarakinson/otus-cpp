#pragma once 

#include "statistics.h"
#include <vector>
#include <string>


class Perc : public IStatistics {
public:
	Perc(int perc) : m_selection{} {    // set percentile value and name in constructor
		set_percentage(perc); 
		set_name(perc);
	} 

    void set_percentage(int perc) { m_perc = perc; }          // set percentile value

	void update(double next) override {
        m_selection.push_back(next);
	}

	void set_name(int);
	double eval() const override;
	const char * name() const override { return m_name.c_str(); }


private:
	std::vector<double> m_selection;     // vector to store values
    int m_perc;                          // percentile value
	// const char * m_name;                 // store name
	std::string m_name;
};

