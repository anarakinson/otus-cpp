#pragma once 

#include <iostream>
#include <fstream>

#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <exception>

#include <algorithm>
#include <iterator>

#include <string>
#include <map>
#include <vector>

#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>


class miss_argument_error : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override { return "\n    Miss argument! \n\n"; }
};


void get_params(int argc, char *argv[], int &num_threads, std::vector<std::string> &file_paths) {

    for (int i = 1; i < argc; ++i) {                       // starts with second argument - 1
        std::string arg{argv[i]};                          // which means first argument
        if (arg == "-t" || arg == "--threads") {           
            if (i + 1 == argc) {                           // if flag is the last arg - break 
                throw miss_argument_error{}; 
            }
            std::string threads{argv[i + 1]};              // if flag is empty - break
            if (threads.empty() || !std::all_of(threads.begin(), threads.end(), ::isdigit)) {
                throw miss_argument_error{}; 
            }
            num_threads = std::stoi(threads);
        }         
        else if ( 
            arg[0] != '-' &&                               // if argument is not flag
            std::string(argv[i - 1])[0] != '-'             // and argument is not value after flag
        ) {
            file_paths.push_back(arg);
        }
    }

}
