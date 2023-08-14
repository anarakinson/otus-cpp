// Read files and prints top k word by frequency

#include <get_params.h>

#include <iostream>
#include <fstream>
#include <sstream>

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


const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::string &filename, Counter &counter, int num_threads);

void print_topk(std::ostream& stream, const Counter&, const size_t k);



int main(int argc, char *argv[]) {

    int num_threads = std::thread::hardware_concurrency();

    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }


    /* ----- START ----- */
    std::cout << "    Using " << num_threads << " threads \n" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    
    for (int i = 1; i < argc; ++i) {
        std::string filename{argv[i]};
        count_words( std::string(filename), freq_dict, num_threads );
    }



    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};


Counter count_parallel(std::string &input, int num_threads, int step) {
    
    Counter counter;
    long long cnt = step;

    std::istringstream stream(input);
    std::string line;
    std::string word;

    while (std::getline(stream, line, '\n')) {
        std::istringstream stream(line);
        if (cnt % num_threads == 0) {
            while (std::getline(stream, word, ' ')) {
                [&counter](const std::string &s) { ++counter[tolower(s)]; } (word);
            }
        }
        ++cnt;
    }

    return counter;

}


void count_words(std::string &filename, Counter& counter, int num_threads) {

    std::vector<std::future<Counter>> threads{};

    std::ifstream input{filename};
    if (!input.is_open()) {
        throw std::runtime_error{"Failed to open '" + filename + "'\n"};
    }

    // std::ifstream in_file{filename};       //open the input file
    // std::stringstream stream;
    // stream << in_file.rdbuf();             //read the file
    // std::string str = stream.str();        //str holds the content of the file

    std::string str;
    std::getline(std::ifstream(filename), str, '\0');


    for (int i = 0; i < num_threads; ++i) {

        threads.emplace_back(
            std::async(
                std::launch::async,
                count_parallel,             
                std::ref(str),
                num_threads,
                i
            )
        );
    }

    for (int i = 0; i < threads.size(); ++i) {
        Counter result = threads[i].get();
        for (auto &pair : result) {
            counter[pair.first] += pair.second;
        }
    }

}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}