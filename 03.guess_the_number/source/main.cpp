#include <iostream>
#include <string>
#include <map>
#include "gameloop.h"
#include "utils.h"


int main(int argc, char **argv) {
    
    int max_val = 100;
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
                max_val = std::stoi(argv[i+1]);
                if (max_val <= 0) {
                    std::cout << "error: maximum value must be positive" << std::endl;
                    return 1; 
                }
            } 
            // check "-level" argument
            else if (arg == "-level") {
                int level = std::stoi(argv[i+1]);
                if (level > 3 || level <= 0) {
                    std::cout << "error: level must be in range (1, 3)" << std::endl;
                    return 1; 
                }
                switch (level) {
                    case 1: max_val = 10; break;
                    case 2: max_val = 50; break;
                    case 3: max_val = 100; break;
                }
            }
        }
    }
    /* ------------------------------------ */
    // start game loop
    game_loop(max_val, dir_path);
    show_results(dir_path);
    return 0;
}