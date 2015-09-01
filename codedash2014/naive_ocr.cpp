#include <iostream>
//#include <map>
#include <vector>
#include <memory>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

int distance(const string& word, const string& dict_word)
{
    if (word == dict_word)
    {
        return 0;
    }

    vector<int> prevRow;
    for (int i = 0; i <= word.length(); i++)
    {
        prevRow.push_back(i);
    }

    for (int i = 0; i < dict_word.length(); i++)
    {
        vector<int> curRow;
        curRow.push_back(prevRow[0]+1);

        for (int j = 1; j <= word.length(); j++)
        {
            if (word[j-1] == dict_word[i])
            {
                curRow.push_back(prevRow[j-1]);
                continue;
            }
            curRow.push_back(std::min({curRow[j-1]+1, prevRow[j-1]+1, prevRow[j]+1}));
        }

        prevRow = curRow;
    }

    return prevRow.back();
}

int main()
{
    //Trie dict;
    vector<string> dict_words;
    vector<string> words;

    int num_words;
    string input;
    cin >> num_words;
    for (int i = 0; i < num_words; i++)
    {
        cin >> input;
        //dict.InsertWord(input);
        dict_words.push_back(input);
    }

    cin >> num_words;
    for (int i = 0; i < num_words; i++)
    {
        cin >> input;
        words.push_back(input);
    }

    //auto total_distance = 0;
    for (auto& word : words)
    {
        auto min_distance = INT_MAX;
        //std::cout << word << std::endl;
        for (auto& dict_word : dict_words)
        {
            auto dist = distance(word, dict_word);
            if (dist < min_distance)
            {
                min_distance = dist;
            }
        }
        std::cout << min_distance << std::endl;
        //total_distance += min_distance;
    }

    //std::cout << total_distance << std::endl;

    return 0;
}
