#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "utils.h"

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}


// get the application directory
std::string parse_dir_path(const std::string &app_path) {

    // get application path
    std::string dir_path = "";
    std::string word = "";
    // split to names without the last name
    for (const char &ch : app_path) {
        if (ch == '/' || ch == '\\') {
            dir_path = dir_path + word;
            word = "";
        }
        word += ch;
    }
    return dir_path;

}


// save results to file
void save_results(std::string path, std::string username, int score) {
    
    // load old results
    std::map<std::string, int> results = load_results(path);
    // rewrite scores.txt file
    std::fstream fsout;
    fsout.open(path + separator() + "scores.txt", std::fstream::out);
    // correction
    if (results[username] > score || results[username] == 0) {
        results[username] = score;
    }
    // write results to file
    for (auto [username, score] : results) {
        fsout << username << " " << score << std::endl;
    }
    fsout.close();

}


// load results from file to map with unique usernames and best results
std::map<std::string, int> load_results(std::string path) {

    std::map<std::string, int> output;

    std::fstream fsin;
    fsin.open(path + separator() + "scores.txt", std::fstream::in);
    if (!fsin.is_open()) {
        std::cout << "error: scores.txt does not exists!" << std::endl;
        return output;
    }
    // read lines from file
    std::string line;
    while (getline(fsin, line)) {
        // split line to words
        std::string username = "";
        std::string word = "";
        for (const char &ch : line) {
            if (ch == ' ') {
                username += word;
                word = "";
            }
            word += ch;
        }
        int score = stoi(word);
        // append pair (username, score) to output map, if current score < last score
        if (output[username] > score || output[username] == 0) {
            output[username] = score;
        }
    }
    fsin.close();

    return output;

}


// show results on standart output
void show_results(std::string path) {
    
    // load results
    std::map<std::string, int> results = load_results(path);
    // show them in output
    std::cout << std::endl;
    std::cout << "best scores:" << std::endl;
    for (auto [username, score] : results) {
        std::cout << username << " - " << score << std::endl;
    }

}

