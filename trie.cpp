#include <map>
#include <set>
#include <string>
#include <iostream>
#include <deque>

struct Obj
{
    Obj()
    {
        i_ = current_id_++;
        std::cout << "Construct Obj(" << i_ << ")\n";
    }

    Obj(const Obj& obj)
    {
        i_ = current_id_++;
        std::cout << "Construct Obj(" << i_ << ") from Obj(" << obj.i_ << ")\n";
    }

    ~Obj()
    {
        std::cout << "Destruct Obj(" << i_ << ")\n";
    }

    int i_;
    static int current_id_;
};

int Obj::current_id_{0};

template <typename MAP>
auto prefix(const MAP &map, std::string key)
{
    std::string after = key;
    if (after.empty())
    {
        return std::make_pair(map.begin(), map.end());
    }
    else if (after.back() != 255)
    {
        after.back()++;
    }
    else
    {
        throw std::runtime_error("I'm lazy today");
    }
    return std::make_pair(map.lower_bound(key), map.lower_bound(after));
}

void dummy2()
{
    throw std::runtime_error("test");
}

void dummy()
{
    Obj obj1;
    Obj obj2;
    Obj obj3 = obj2;
    dummy2();
    
    Obj obj4;
}

int main()
{
    std::map<std::string, int> table;
    table["a"] = 3;
    table["aabca"] = 6;
    table["aabd"] = 4;
    table["aabc"] = 5;
    table["ac"] = 7;

    table.emplace("aabde", 3);

    {
        auto it = table.find("a");
        if (it == table.end())
            std::cout << "not found" << std::endl;
        else
            std::cout << it->first << "," << it->second << std::endl;
    }

    for (const auto &[key, v] : table)
    {
        std::cout << key <<  "," << v << std::endl;
    }

    {
        auto begin = table.lower_bound("aa");
        auto end = table.lower_bound("ab");
        for (auto it = begin; it != end; it++)
        {
            std::cout << it->first << "," << it->second << std::endl;
        }
    }

    {
        std::multimap<std::string, int> table2;
        table2.emplace("aa", 3);
        table2.emplace("ab", 4);
        table2.emplace("aa", 5);
        table2.emplace("aa", 6);

        auto [begin,end] = table2.equal_range("aa");

        for (auto it = begin; it != end; it++)
        {
            std::cout << it->first << "," << it->second << std::endl;
        }
    }

    {
        auto [begin,end] = prefix(table, "");

        for (auto it = begin; it != end; it++)
        {
            std::cout << it->first << "," << it->second << std::endl;
        }
    }

    try
    {
        dummy();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught " << e.what() << '\n';
    }
    
    // std::map : comparaison = O(log(taille))
    // trie : O(key_length)
}

/*

Functions + static

Tas



Pile ^

*/