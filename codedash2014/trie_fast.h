#include <vector>
#include <map>
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
    //bool Find(const std::vector<std::vector<char>>& prefixes, size_t index, const std::string& curstr, std::vector<std::pair<std::string, Trie*>>& resultNodes);
    //bool FindAll(const std::string& prefix, std::vector<std::string>& possibleWords);
    //bool FindAll(const std::vector<std::vector<char>>& prefixes, std::vector<std::string>& possibleWords);

    //std::vector<std::pair<char, Trie*>> children();
    Trie** children();
    bool isWord();

private:
    //bool FindAllHelper(const std::string& curstr, std::vector<std::string>& possibleWords);
    //std::map<char, std::unique_ptr<Trie>> children_;
    Trie* children_[MAX_CHILDREN];
    bool isWord_;
};
