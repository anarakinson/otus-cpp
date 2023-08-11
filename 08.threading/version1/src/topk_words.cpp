// Read files and prints top k word by frequency

#include <get_params.h>
// #include <text_processing.h>

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

Counter count_words(std::string file_path); 

void print_topk(std::ostream& stream, const Counter&, const size_t k);

Counter m_count(std::string &file_path, int step, int num_threads);


int main(int argc, char *argv[]) {

    std::vector<std::string> file_paths{};
    int num_threads = std::thread::hardware_concurrency();

    // get params
    try {
        get_params(argc, argv, num_threads, file_paths);
    } catch (std::exception &err) {
        std::cerr << err.what();
        return EXIT_FAILURE;
    }

    // check if params is correct
    if (num_threads <= 0) {
        std::cerr << "\n\n"
                    << "    Number of threads must be greater than zero! \n";
        return EXIT_FAILURE;
    }
    if (num_threads > 20) {
        std::cerr << "\n\n"
                    << "    Too many threads! \n\n";
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        std::cerr << "\n\n"
                  << "    [USAGE]  Run application for files:   topk_words [FILES...] \n"
                  << "    [OPTIONALLY] Set number of threads:   topk_words --threads X [FILES...] \n"
                  << "    [OPTIONALLY]                          topk_words -t X [FILES...] \n"
                  << "    [OPTIONALLY] Where X - number of threads \n\n";
        return EXIT_FAILURE;
    }


    /* ----- START ----- */
    std::cout << "    Using " << num_threads << " threads \n" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    std::vector<std::future<Counter>> tasks{};

    for (std::string file_path : file_paths) {
        tasks.push_back(std::async(std::launch::async, count_words, file_path));
    }

    for (int i = 0; i < tasks.size(); ++i) {
        Counter future = tasks[i].get();
        // Counter future = tasks[i];
        for (auto &pair : future) {
            freq_dict[pair.first] += pair.second;
        }
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

Counter count_words(std::string file_path) {

    Counter counter;
    std::ifstream stream{file_path};
    if (!stream.is_open()) {
        std::cerr << "Failed to open file " << file_path << '\n';
        return {};
    }    

    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });  
    return counter;  
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