#include "trie_fast.h"


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
