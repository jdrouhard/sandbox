#include "trie.h"

Trie::Trie()
{
}

Trie::~Trie()
{
}

bool Trie::InsertWord(const std::string& remaining)
{
    if (remaining.empty())
    {
        isWord_ = true;
        return true;
    }

    if (!children_.count(remaining[0]))
    {
        children_.emplace(remaining[0], std::unique_ptr<Trie>(new Trie()));
    }

    return children_[remaining[0]]->InsertWord(remaining.substr(1));
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

    if (children_.count(prefix[0]))
    {
        return children_[prefix[0]]->Find(prefix.substr(1));
    }
    else
    {
        return nullptr;
    }
}

bool Trie::Find(const std::vector<std::vector<char>>& prefixes, size_t index, const std::string& curstr, std::vector<std::pair<std::string, Trie*>>& resultNodes)
{
    if (index >= prefixes.size())
    {
        resultNodes.emplace_back(curstr, this);
        return true;
    }

    for (char c : prefixes[index])
    {
        if (children_.count(c))
        {
            children_[c]->Find(prefixes, index + 1, curstr + c, resultNodes);
        }
    }

    return true;
}

bool Trie::FindAll(const std::string& prefix, std::vector<std::string>& possibleWords)
{
    possibleWords.clear();

    auto start = Find(prefix);

    if (start)
    {
        return start->FindAllHelper(prefix, possibleWords);
    }

    return false;
}

bool Trie::FindAll(const std::vector<std::vector<char>>& prefixes, std::vector<std::string>& possibleWords)
{
    std::vector<std::pair<std::string, Trie*>> startNodes;
    if (!Find(prefixes, 0, "", startNodes))
    {
        return false;
    }

    for (auto node : startNodes)
    {
        node.second->FindAllHelper(node.first, possibleWords);
    }

    return true;
}

bool Trie::FindAllHelper(const std::string& curstr, std::vector<std::string>& possibleWords)
{
    if (isWord_)
    {
        possibleWords.push_back(curstr);
    }
    if (children_.empty())
    {
        return true;
    }

    for (auto& child : children_)
    {
        //iter->second->FindAllHelper(curstr + iter->first, possibleWords);
        child.second->FindAllHelper(curstr + child.first, possibleWords);
    }

    return true;
}

std::vector<std::pair<char, Trie*>> Trie::children()
{
    std::vector<std::pair<char, Trie*>> value;
    for (auto& child : children_)
    {
        value.emplace_back(child.first, child.second.get());
    }
    return value;
}

bool Trie::isWord()
{
    return isWord_;
}
