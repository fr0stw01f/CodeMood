#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <future>
#include <algorithm>

#include "utils.h"

using WordCountMapType = std::unordered_map<std::string, std::size_t>;

int main(int argc, const char** argv)
{
    std::vector<std::future<WordCountMapType>> futures;
    for (int argNum = 1; argNum < argc; ++argNum)
    {
        std::cerr << "FILENAME:" << argv[argNum] << std::endl;
        futures.push_back(std::async([=]{return wordsInFile(argv[argNum]);}));
    }

    WordCountMapType wordCounts;
    for (auto& future : futures)
    {
        auto results = future.get();
        for (const auto& wordCount: results)
        {
            wordCounts[wordCount.first] += wordCount.second;
        }
    }
    std::cout << wordCounts.size() << " words found. Most common:\n";
    const size_t maxWordsToShow = 20;
    showCommonWords(std::begin(wordCounts), std::end(wordCounts), std::min(wordCounts.size(), maxWordsToShow));
    return 0;
}
