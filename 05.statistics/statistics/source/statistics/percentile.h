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

	const char * name() const override { 
        std::string str_name = "perc" + std::to_string(m_perc);
        char* char_array = new char[str_name.length() + 1];
        // strcpy_s(char_array, str_name.c_str());
        strcpy_s(char_array, sizeof(char_array), str_name.c_str());
        return char_array; 
    }

private:
	std::vector<double> m_selection;
    int m_perc;
};

