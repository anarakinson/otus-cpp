#pragma once 

#include <string>
#include <map>

void save_results(std::string, std::string, int);
void show_results(std::string);
std::string parse_dir_path(const std::string&);
std::map<std::string, int> load_results(std::string);