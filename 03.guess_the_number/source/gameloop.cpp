#include <iostream>
#include <limits>

#include <cstdlib>
#include <ctime>
#include <string>

#include "gameloop.h"
#include "utils.h"



// return random number in range (0, max_value)
int get_random_num(int max_value) {

	std::srand(std::time(nullptr)); // set seed for random generator with current time
	int random_value = std::rand() % max_value;
	return random_value;

}

    
// start game main loop
void game_loop(int max_value, std::string dir_path) {
    
    // input user's name
    std::string username;
    int score = 0;
    std::cout << "Hi! Enter your name, please: ";
    getline(std::cin, username);

    // initialize target
    const int target = get_random_num(max_value);
    int pred;

    while (true) {
        std::cout << "input a number: ";  
        std::cin >> pred;

        // check if input is integer
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "input must be integer\n";
            continue;
        }

        // increase score
        ++score;

        // check if win
        if (pred > target) {
            std::cout << pred << " greater than target" << std::endl;
        } else if (pred < target) {
            std::cout << pred << " less than target" << std::endl;
        } else if (pred == target) {
            std::cout << "you win!" << std::endl;
            break;
        }
    }

    // save results
    std::cout << "your score: " << score << std::endl; 
    save_results(dir_path, username, score);
}
