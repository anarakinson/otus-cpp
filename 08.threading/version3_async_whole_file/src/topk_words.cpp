// Read files and prints top k word by frequency

#include <get_params.h>

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


Counter count_parallel(std::string &filename, int num_threads, int step) {
    
    std::ifstream input{filename};
    if (!input.is_open()) {
        throw std::runtime_error{"Failed to open '" + filename + "'\n"};
    }

    Counter counter;

    long long cnt = step;
    std::string word;
    while (input >> word) {
        if (cnt % num_threads == 0) {
            [&counter](const std::string &s) { ++counter[tolower(s)]; } (word);
        }
        ++cnt;
    }

    return counter;

}


void count_words(std::string &filename, Counter& counter, int num_threads) {

    std::vector<std::future<Counter>> threads{};

    for (int i = 0; i < num_threads; ++i) {

        threads.emplace_back(
            std::async(
                std::launch::async,
                count_parallel,             
                filename,
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