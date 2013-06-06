#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <future>
#include <algorithm>

using WordCountMapType = std::unordered_map<std::string, std::size_t>;

WordCountMapType wordsInFile(const char* fileName);

template<typename MapIt>
void showCommonWords(MapIt begin, MapIt end, std::size_t n)
{
    std::vector<MapIt> wordIters;
    wordIters.reserve(distance(begin, end));
    for (auto i = begin; i != end; ++i) wordIters.push_back(i);

    auto sortedRangeEnd = std::begin(wordIters) + n;
    std::partial_sort(std::begin(wordIters), sortedRangeEnd, std::end(wordIters), [](MapIt it1, MapIt it2){
        return it1->second > it2->second;
    });

    for (auto it = wordIters.begin(); it != sortedRangeEnd; ++it)
    {
        std::printf(" %-10s%10zu\n", (*it)->first.c_str(), (*it)->second);
    }
}


#endif
