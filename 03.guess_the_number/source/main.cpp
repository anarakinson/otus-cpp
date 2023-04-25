#include <iostream>
#include <string>
#include <map>

#include "gameloop.h"
#include "utils.h"


int main(int argc, char **argv) {
    
    int max_val = 100;
    int level = 0;
    int argument_counter = 0;

    std::string app_path{argv[0]};
    std::string dir_path = parse_dir_path(app_path);
    
    // parse arguments
    if (argc >= 2) {
        for (int i=0; i<argc; ++i) {
            std::string arg{argv[i]};
            // check if there is only one possible argument: max or level, or duplicates
            if (arg == "-max" || arg == "-level") {
                ++argument_counter;
                if (argument_counter >=2) {
                    std::cout << "error: choose only one option, -max or -level" << std::endl;
                    return 1;
                }
            }
            // check "-table" argument 
            if (arg == "-table") {
                show_results(dir_path); 
                return 0;
            }
            // check "-max" argument
            if (arg == "-max") {
                // check if argument is number and not null 
                std::string next_arg{""};
                if (argv[i+1] != NULL) {
                    next_arg = argv[i+1];
                };
                bool success = is_number(next_arg);
                // and convert it
                if (success) {
                    max_val = stol(next_arg);
                }
                if (!success || (success && max_val <= 0)) {
                    std::cout << "error: maximum value must be positive number" << std::endl;
                    return 1; 
                }
            } 
            // check "-level" argument
            else if (arg == "-level") {
                // check if argument is number and not null      
                std::string next_arg{""};
                if (argv[i+1] != NULL) {
                    next_arg = argv[i+1];
                };
                bool success = is_number(next_arg);
                // and convert it
                if (success) {
                    level = stol(next_arg);
                    switch (level) {
                        case 1: max_val = 10; break;
                        case 2: max_val = 50; break;
                        case 3: max_val = 100; break;
                    }
                }
                if (!success || (success && (level > 3 || level <= 0))) {
                    std::cout << "error: level must be number in range (1, 3)" << std::endl;
                    return 1; 
                }
            }
        }
    }
    /* ------------------------------------ */
    // start game loop
    std::cout << "start" << std::endl;
    game_loop(max_val, dir_path);
    show_results(dir_path);
    return 0;
}