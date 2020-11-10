#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

enum class FindResult
{
    Found,
    Prefix,
    NotFound
};

struct Node
{
    std::size_t children[256];
    bool is_leaf;
};

std::size_t empty_child = -1;
Node make_empty_node()
{
    Node retval;
    retval.is_leaf = false;
    for (auto &c : retval.children)
        c = empty_child;
    return retval;
}

Node empty_node = make_empty_node();

using Trie = std::vector<Node>;
using Position = std::size_t;

Trie empty_trie{empty_node};

Position insert_into_trie(Trie &trie, std::string_view key, Position root = 0)
{
    if (trie.size() <= root)
        throw std::runtime_error("Out of bond access");
    Node &node = trie[root];
    if (key.empty())
    {
        node.is_leaf = true;
        return root;
    }
    auto c = key[0];
    if (node.children[c] == empty_child)
    {
        node.children[c] = trie.size();
        trie.emplace_back(empty_node);
    }
    return insert_into_trie(trie, key.substr(1), node.children[c]);
}

FindResult find(const Trie &trie, std::string_view key, Position root = 0)
{
    if (trie.size() <= root)
        throw std::runtime_error("Out of bond access");

    const Node &node = trie[root];

    if (key.empty())
        return node.is_leaf ? FindResult::Found : FindResult::Prefix;

    auto c = key[0];

    if (node.children[c] == empty_child)
        return FindResult::NotFound;
    return find(trie, key.substr(1), node.children[c]);
}

int main()
{
    Trie trie = empty_trie;
    while (true)
    {
        std::string command;
        std::string data;
        std::cout << "enter [Insert|Find|Quit] string" << std::endl;
        std::cin >> command >> data;
        if (command == "Quit")
        {
            return 0;
        }
        else if (command == "Insert")
        {
            Position position = insert_into_trie(trie, data);
            std::cout << "Inserted " << data << " at " << position << std::endl;
        }
        else if (command == "Find")
        {
            auto res = find(trie, data);
            if (res == FindResult::Found)
                std::cout << data << " was found in the trie" << std::endl;
            else if (res == FindResult::Prefix)
                std::cout << data << " is a prefix of some data" << std::endl;
            else
                std::cout << data << " was not in the trie" << std::endl;
        }
        else
        {
            std::cout << "Unknown command : " << command << std::endl;
        }
    }
}
