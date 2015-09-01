#include "trie.h"

#include <climits>
#include <fstream>
#include <future>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>

void distance_helper(Trie* node, char letter, const std::string& word, int* prevRow, int& minCost)
{
    auto columns = word.size() + 1;
    auto minRowCost = INT_MAX;
    int* v = new int[columns];
    v[0] = prevRow[0] + 1;
    for (int i = 1; i < columns; ++i)
    {
        auto insertCost = v[i-1] + 1;
        auto deleteCost = prevRow[i] + 1;

        int replaceCost;
        if (word[i-1] != letter)
        {
            replaceCost = prevRow[i-1] + 1;
        }
        else
        {
            replaceCost = prevRow[i-1];
        }

        v[i] = std::min({insertCost, deleteCost, replaceCost});
        minRowCost = std::min(minRowCost, v[i]);
    }

    if (v[columns-1] < minCost && node->isWord())
    {
        minCost = v[columns-1];
    }

    if (minRowCost < minCost)
    {
        auto children = node->children();
        for (auto& c : children)
        {
            distance_helper(c.second, c.first, word, v, minCost);
            if (minCost == 1) return;
        }
    }

    delete[] v;
}

int distance(const std::string& input, Trie* dict)
{
    if (dict->Contains(input))
    {
        return 0;
    }

    int* v = new int[input.size()+1];
    for (int i = 0; i <= input.size(); ++i)
    {
        v[i] = i;
    }

    auto children = dict->children();
    auto minCost = INT_MAX;

    std::vector<std::thread> threads;
    auto chunks = 4;
    auto chunkSize = children.size()/chunks;
    for (int i = 0; i <= chunks; ++i)
    {
        threads.emplace_back([i, chunkSize, &v, &children, &minCost, &input](){
            for (auto iter = children.begin()+i*chunkSize, iter_end=children.begin()+std::min((i+1)*chunkSize, children.size()); iter != iter_end; ++iter)
            {
                distance_helper(iter->second, iter->first, input, v, minCost);
                if (minCost == 1) break;
            }
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    delete[] v;

    return minCost;
}

int main()
{
    Trie dict;
    std::ifstream dictfile("twl06.txt");
    std::string s;
    while (dictfile >> s)
    {
        dict.InsertWord(s);
    }
    dictfile.close();

    std::vector<std::string> words;
    std::string input;
    while (std::cin >> input)
    {
        std::istringstream buffer(input);
        std::vector<std::string> temp {std::istream_iterator<std::string>(buffer),
                                       std::istream_iterator<std::string>()};
        for (auto& w : temp)
        {
            words.push_back(std::move(w));
        }
    }

    auto totalDistance = 0;
    for (auto& word : words)
    {
        //auto dist = distance(word, &dict);
        totalDistance += distance(word, &dict);
        //std::cout << word << ": " << dist << std::endl;
    }

    std::cout << totalDistance << std::endl;
    return 0;
}
