#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <future>
#include <algorithm>

using WordCountMapType = std::unordered_map<std::string, std::size_t>;

WordCountMapType wordsInFile(const char* fileName)
{
    std::ifstream file(fileName);
    WordCountMapType wordCounts;

    for (std::string word; file >> word; )
    {
        ++wordCounts[word];
    }
    return wordCounts;
}
