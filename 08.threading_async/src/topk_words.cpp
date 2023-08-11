// Read files and prints top k word by frequency

#include <get_params.h>
#include <text_processing.h>

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
    for (std::string file_path : file_paths) {
        try {
            count_words(file_path, freq_dict, num_threads);
        } catch (std::exception &err) {
            std::cerr << err.what();
            return EXIT_FAILURE;
        }
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

