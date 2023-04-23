#pragma once 

#include <string>
#include <map>

void save_results(const std::string&, const std::string&, int);
void show_results( const std::string&);
std::string parse_dir_path(const std::string&);
std::map<std::string, int> load_results(const std::string&);