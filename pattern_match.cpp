#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <cctype>
#include <cstdlib>

class Trie
{
public:
    Trie() : isWord_(false) {}
    virtual ~Trie() {}

    void AddWord(const std::string& word);
    std::list<std::string> MatchWords(const std::string& pattern) const;

private:
    void MatchWordsHelper(const std::string& pattern, int depth, const std::string& wordSoFar, std::list<std::string>& results) const;
    std::map<char, Trie> children_;
    bool isWord_;
};

void Trie::AddWord(const std::string& word)
{
    if (word.length() == 0)
    {
        isWord_ = true;
        return;
    }

    children_[word[0]].AddWord(word.substr(1));
}

std::list<std::string> Trie::MatchWords(const std::string& pattern) const
{
    std::list<std::string> results;

    MatchWordsHelper(pattern, 0, "", results);

    return results;
}

void Trie::MatchWordsHelper(const std::string& pattern, int depth, const std::string& wordSoFar, std::list<std::string>& results) const
{
    if (pattern.length() == 0 && depth == 0)
    {
        if (isWord_)
        {
            results.push_back(wordSoFar);
        }
        return;
    }
    if (depth > 0)
    {
        for (std::map<char, Trie>::const_iterator it = children_.begin(), it_end = children_.end(); it != it_end; ++it)
        {
            it->second.MatchWordsHelper(pattern, depth - 1, wordSoFar + it->first, results);
        }
        return;
    }
    if (isalpha(pattern[0]))
    {
        const std::map<char, Trie>::const_iterator child = children_.find(pattern[0]);
        if (child != children_.end())
        {
            child->second.MatchWordsHelper(pattern.substr(1), 0, wordSoFar + child->first, results);
        }
        return;
    }
    if (isdigit(pattern[0]))
    {
        depth = atoi(&pattern[0]);
        MatchWordsHelper(pattern.substr(1), depth, wordSoFar, results);
        return;
    }
}

int main()
{
    std::string pattern;
    std::cin >> pattern;

    Trie t;

    std::ifstream dictfile("brit-a-z.txt");
    std::string s;
    while (dictfile >> s)
    {
        t.AddWord(s);
    }
    dictfile.close();

    std::list<std::string> results = t.MatchWords(pattern);

    for (std::list<std::string>::const_iterator it = results.begin(), it_end = results.end(); it != it_end; ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
