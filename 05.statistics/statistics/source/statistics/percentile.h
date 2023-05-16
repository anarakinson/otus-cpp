#pragma once 

#include "statistics.h"
#include <vector>


class Perc90 : public IStatistics {
public:
	Perc90() : m_selection{} { set_percentage(90); }

    void set_percentage(int perc) { m_perc = perc; }

	void update(double next) override {
        m_selection.push_back(next);
	}

	double eval() const override;

	const char * name() const override { return "perc90"; }

private:
	std::vector<double> m_selection;
    int m_perc;
};

class Perc95 : public Perc90 {
    public:
        Perc95() { set_percentage(95); }

        const char * name() const override { return "perc95"; }
};


