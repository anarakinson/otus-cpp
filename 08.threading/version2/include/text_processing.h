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



using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::string &file_path, Counter&, int num_threads);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

Counter m_count(std::string &file_path, int step, int num_threads);



std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(
        std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch) { return std::tolower(ch); }
    );
    return lower_str;
};


//
Counter m_count(std::string &file_path, int step, int num_threads) {
    std::ifstream stream{file_path};
    if (!stream.is_open()) {
        throw std::runtime_error{"Failed to open '" + file_path + "'\n"};
    }
    std::istream_iterator<std::string> iterator{stream};
    std::istream_iterator<std::string> last_word{};
    std::advance(iterator, step); 

    Counter counter{};
    long long x = 0;

    for (; iterator != last_word; ++iterator) {
        if (x % num_threads == 0) {
            [&counter](const std::string &s) { ++counter[tolower(s)]; } (*iterator);
        }
        ++x;
    }
    return counter;
}


void count_words(std::string &file_path, Counter &counter, int num_threads) {

    if (num_threads == 1) {
        std::ifstream stream{file_path};
        if (!stream.is_open()) {
            throw std::runtime_error{"Failed to open '" + file_path + "'\n"};
        }

        /* ---------------------------------------------------------------- */

        // std::for_each(
        //     std::istream_iterator<std::string>(stream),
        //     std::istream_iterator<std::string>(),
        //     [&counter](const std::string &s) { ++counter[tolower(s)]; }
        // );
        // // Elapsed time is 61635 us

        /* ---------------------------------------------------------------- */

        std::istream_iterator<std::string> iterator{stream};
        std::istream_iterator<std::string> last_word{};
        for (; iterator != last_word; ++iterator) {
            [&counter](const std::string &s) { ++counter[tolower(s)]; } (*iterator);
        }
        // Elapsed time is 62166 us
    }

    else {  
        // std::vector<Counter> tasks{};
        std::vector<std::future<Counter>> tasks{};
        tasks.reserve(num_threads);

        for (int i = 0; i < num_threads; ++i) {

            tasks.push_back( 
                std::async(
                    std::launch::async, 
                    m_count,
                    std::ref(file_path),
                    i,
                    num_threads
                )
            );

            // tasks.push_back( 
            //     m_count(
            //         file_path,
            //         i,
            //         num_threads
            //     )
            // );
        }
    
        for (int i = 0; i < tasks.size(); ++i) {
            Counter future = tasks[i].get();
            // Counter future = tasks[i];
            for (auto &pair : future) {
                counter[pair.first] += pair.second;
            }
        }
        // Elapsed time is 62166 us
    }

}

// 266 the
// 134 is
// 133 of
// 122 to
// 118 a
// 97 in
// 83 and
// 72 {
// 69 this
// 64 it


void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), 
        std::begin(words) + k, 
        std::end(words), 
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; } 
    );

    std::for_each(
        std::begin(words), 
        std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(5) << pair->second 
                   << " " << pair->first
                   << '\n';
        }
    );
}
