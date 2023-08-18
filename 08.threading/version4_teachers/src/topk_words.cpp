#include <sstream>
#include <string>
#include <map>
#include <future>
#include <random>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <functional>

using Pos = std::istringstream::pos_type;
using Dict = std::map<std::string, size_t>;

Dict countWords(std::istringstream &text, Pos endPos) {
    std::map<std::string, size_t> counter;
    std::string word;

    while (text.tellg() != endPos && text >> word) {
        ++counter[word];
    }
    return counter;
}


Dict countWordsSingle(const std::string& text) {
    std::istringstream stream(text);
    return countWords(stream, text.size());
}

/**
 * @brief Считывает символы из потока до достижения eof или пока условие cond(sym) не станет ложным
 * @return положение последнего прочитанного символа (или eof)
 */
template <class Cond>
Pos walkUntil(Pos offset, std::istringstream& stream, Cond&& cond) {
    Pos pos = offset;
    stream.seekg(pos);
    char symbol;

    while (stream.get(symbol), stream.good() && cond(symbol)) {
        pos = stream.tellg();
    }
    return pos;
}

/**
 * @brief Выполняет разбиение текста на блоки по возможности близкого размера
 * @return возвращает позиции конца каждого блока в тексте
 */
std::vector<std::pair<Pos, Pos>> endOfBlocksPos(const std::string& text, size_t blocksCount) {
    std::vector<std::pair<Pos, Pos>> blocks(blocksCount);
    const auto lastBlockEnd = Pos(text.size());
    const auto estBlockSize = std::max(Pos(lastBlockEnd / blocksCount), Pos(1));

    std::istringstream stream(text);
    Pos nextBegin = {};

    for (auto& [beg, end]: blocks) {
        beg = nextBegin;
        end = std::min(beg + estBlockSize, lastBlockEnd);
        auto isSpace = [] (char symbol) -> bool {  return std::isspace(symbol); };
        // идем до конца слова
        end = walkUntil(end, stream, std::not_fn(isSpace));
        // идем до начала слова
        nextBegin = walkUntil(end, stream, isSpace);
    }
    return blocks;
}

using Futures = std::vector<std::future<Dict>>;

Dict mergeDicts(const std::vector<Dict>& dicts) {
    using DictIt = Dict::const_iterator;
    struct ItPair {
        DictIt it;
        DictIt end;

        bool isEnd() const { return it == end; }
    };

    std::vector<ItPair> iters;
    size_t wordsCount{};

    for (auto& d: dicts) {
        iters.push_back({d.begin(), d.end()});
        wordsCount += d.size();
    }
    Dict result;

    for (size_t i = 0; i < wordsCount; ++i) {
        auto less = [] (const ItPair& lhs, const ItPair& rhs) {
            if (lhs.isEnd() || rhs.isEnd()) {
                return !lhs.isEnd();
            }
            return lhs.it->first < rhs.it->first;
        };
        DictIt& min = std::min_element(iters.begin(), iters.end(), less)->it;

        if (result.empty()) {
            result.insert(*min);
        } else {
            auto last = std::prev(result.end());

            if (last->first == min->first) {
                last->second += min->second;
            } else {
                result.insert(result.end(), *min);
            }
        }
        ++min;
    }
    return result;
}

Dict mergeByHands(Futures&& futures) {
    std::vector<Dict> dicts;
    dicts.reserve(futures.size());

    for (auto& f: futures) {
        dicts.push_back(std::move(f.get()));
    }
    return mergeDicts(dicts);
}

Dict countWordsMulti(const std::string& text) {
    const auto threads = std::thread::hardware_concurrency();

    const auto blocks = endOfBlocksPos(text, threads);
    std::vector<std::future<Dict>> futures;

    for (auto& [beg, end]: blocks) {
        futures.push_back(std::async(std::launch::async, [&text, beg, end]() {
            std::istringstream stream(text);
            stream.seekg(beg);
            return countWords(stream, end);
        }));
    }
    Dict result;

    return mergeByHands(std::move(futures));
}


std::string makeRandomWorld(std::mt19937_64& mt, size_t size) {
    std::uniform_int_distribution<char> letters('a', 'z');
    std::string str(size, ' ');

    for (auto& symbol: str) {
        symbol = letters(mt);
    }
    return str;
}

template <class Time>
double seconds(Time begin, Time end) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
}

int main(int argc, char *argv[]) {
    const size_t words = 10'000'000;
    std::string text;

    std::mt19937_64 mt;
    std::uniform_int_distribution<size_t> lengths(3, 6);

    for (size_t i = 0; i < words; ++i) {
        const size_t length = lengths(mt);
        text.append(makeRandomWorld(mt, length)).append(" ");
    }

    auto start = std::chrono::high_resolution_clock::now();
    Dict single = countWordsSingle(text);
    auto singleEnd = std::chrono::high_resolution_clock::now();
    Dict multi = countWordsMulti(text);
    auto multiEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Ok: " << std::boolalpha << (single == multi) << std::endl;

    std::cout << "single " << seconds(start, singleEnd) << "s" << std::endl;
    std::cout << "multi " << seconds(singleEnd, multiEnd) << "s" << std::endl;
}
