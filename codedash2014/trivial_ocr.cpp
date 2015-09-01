#include <iostream>
#include <vector>
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

    int* prev_row = new int[word.length()+1];
    int* cur_row = new int[word.length()+1];

    for (int i = 0; i <= word.length(); i++)
    {
        prev_row[i] = i;
    }

    for (int j = 0; j < dict_word.length(); j++)
    {
        cur_row[0] = prev_row[0] + 1;

        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == dict_word[j])
            {
                cur_row[i+1] = prev_row[i];
                continue;
            }
            cur_row[i+1] = std::min({cur_row[i]+1, prev_row[i]+1, prev_row[i+1]+1});
        }

        for (int i = 0; i <= word.length(); i++)
        {
            prev_row[i] = cur_row[i];
        }
    }

    auto ret_val = prev_row[word.length()];

    delete[] cur_row;
    delete[] prev_row;

    return ret_val;
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
