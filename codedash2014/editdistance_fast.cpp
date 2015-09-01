#include <algorithm>
#include <climits>
#include <fstream>
#include <future>
#include <iostream>
#include <list>
#include <thread>

#include <vector>
#include <memory>

#define MAX_CHILDREN 26

class Trie
{
public:
    Trie();
    virtual ~Trie();

    bool InsertWord(const std::string& word);
    bool Contains(const std::string& word);

    Trie* Find(const std::string& prefix);

    Trie** children();
    bool isWord();

private:
    //bool FindAllHelper(const std::string& curstr, std::vector<std::string>& possibleWords);
    //std::map<char, std::unique_ptr<Trie>> children_;
    Trie* children_[MAX_CHILDREN];
    bool isWord_;
};

Trie::Trie()
{
    for (auto i = 0; i < MAX_CHILDREN; ++i)
    {
        children_[i] = nullptr;
    }
}

Trie::~Trie()
{
    for (int i = 0; i < MAX_CHILDREN; ++i)
    {
        if (children_[i] != nullptr)
        {
            delete children_[i];
        }
    }
}

bool Trie::InsertWord(const std::string& remaining)
{
    if (remaining.empty())
    {
        isWord_ = true;
        return true;
    }

    auto index = (int)(remaining[0]-'a');
    if (children_[index] == nullptr)
    {
        children_[index] = new Trie();
    }

    return children_[index]->InsertWord(remaining.substr(1));
}

bool Trie::Contains(const std::string& word)
{
    auto node = Find(word);
    if (node)
    {
        return node->isWord_;
    }
    else
    {
        return false;
    }
}

Trie* Trie::Find(const std::string& prefix)
{
    if (prefix.empty())
    {
        return this;
    }

    auto index = (int)(prefix[0]-'a');
    if (children_[index] != nullptr)
    {
        return children_[index]->Find(prefix.substr(1));
    }
    else
    {
        return nullptr;
    }
}


Trie** Trie::children()
{
    return children_;
}

bool Trie::isWord()
{
    return isWord_;
}

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
        for (int i = 0; i < MAX_CHILDREN; ++i)
        {
            if (children[i] != nullptr)
            {
                distance_helper(children[i], (char)(i+'a'), word, v, minCost);
                if (minCost == 1) return;
            }
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
    auto chunkSize = MAX_CHILDREN/chunks;
    for (int i = 0; i <= chunks; ++i)
    {
        threads.emplace_back([i, chunkSize, &v, &children, &minCost, &input](){
            for (auto j = i*chunkSize; j < std::min((i+1)*chunkSize, MAX_CHILDREN); ++j)
            {
                if (children[j] != nullptr)
                {
                    distance_helper(children[j], (char)(j+'a'), input, v, minCost);
                    if (minCost == 1) break;
                }
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
    std::list<std::string> words;
    int num_words;
    std::string input;
    std::cin >> num_words;
    for (int i = 0; i < num_words; i++)
    {
        std::cin >> input;
        dict.InsertWord(input);
    }

    std::cin >> num_words;
    for (int i = 0; i < num_words; i++)
    {
        std::cin >> input;
        words.push_back(input);
    }

    //auto totalDistance = 0;
    for (auto& word : words)
    {
        auto dist = distance(word, &dict);
        std::cout << dist << std::endl;
        //totalDistance += dist;
        //std::cout << word << ": " << dist << std::endl;
    }

    //std::cout << totalDistance << std::endl;
    return 0;
}
