#include "trie.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    Trie dict;
    std::ifstream dictfile("brit-a-z.txt");
    std::string s;
    while (dictfile >> s)
    {
        dict.InsertWord(s);
    }
    dictfile.close();

    std::vector<std::vector<char>> const keypad =
        { {}, {}, {'a', 'b', 'c'}, {'d', 'e', 'f'},
        {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'}, {'p', 'q', 'r', 's'},
        {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'} };

    std::string input;
    int pos = 0;
    while (std::cin >> input)
    {
        std::vector<std::vector<char>> inputChars;
        for (auto c : input)
        {
            std::istringstream istr(std::string{c});
            istr >> pos;
            inputChars.push_back(keypad[pos]);
        }
        std::vector<std::string> words;
        dict.FindAll(inputChars, words);
        //dict.FindAll({{'p', 'r', 's'}, {'m', 'n', 'o'}, {'j', 'k', 'l'}, {'d', 'e', 'f'}}, words);
        for (auto s : words)
        {
            std::cout << s << std::endl;
        }
    }
    return 0;
}
