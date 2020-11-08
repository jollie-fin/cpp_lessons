#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

int fibonacci(int n)
{
    std::vector<int> F = {1,1};
    F.resize(n+2);
    for (int i = 2; i < n; i++)
    {
        F[i] = F[i-1] + F[i-2];
    }
    return F.back();
}

int fibonacci_memo_impl(int n, std::vector<int> &F)
{
    if (n < 2)
        return 1;

    if (F[n] > 0)
        return F[n];

    int retval = fibonacci_memo_impl(n-1, F) + fibonacci_memo_impl(n-2, F);

    F[n] = retval;
    return retval;
}

int fibonacci_memo(int n)
{
    std::vector<int> F(n+1);
    return fibonacci_memo_impl(n, F);
}

//lc[i] : somme des mots de i à end
int line_length(const std::vector<int> &lengths, int start, int end, std::vector<int> &lc)
{
    if (lc[start] != std::numeric_limits<int>::max())
        return lc[start];
    int retval = 0;
    if (start < end)
    {
        retval = line_length(lengths, start + 1, end, lc);
        retval += lengths[start];
        if (start < end - 1)
            retval++;
    }
    lc[start] = retval;
    return retval;
}

int word_wrap_impl(const std::vector<int> &lengths, int end, std::vector<int> &C, int line_width)
{
    if (end == 0)
        return 0;
    if (C[end] != std::numeric_limits<int>::max())
        return C[end];

    std::vector<int> lc(end, std::numeric_limits<int>::max());

    int retval = std::numeric_limits<int>::max();
    for (int i = 0; i < end; i++)
    {
        int cost = line_width - line_length(lengths, i, end, lc);
        cost = cost * cost;

        retval = std::min(retval, word_wrap_impl(lengths, i, C, line_width) + cost);
    }

    C[end] = retval;
    return retval;
}

int word_wrap(const std::vector<int> &lengths, int line_width)
{
    std::vector<int> C(lengths.size() + 1, std::numeric_limits<int>::max());
    return word_wrap_impl(lengths, lengths.size(), C, line_width);
}

/*
    bottom-up : prog dynamique
    top-bottom : memoization
*/

int icarus(int n, std::vector<bool> &save)
{
    if (n < save.size() && save[n])
        return n;

    if (n >= save.size())
        save.resize(n * 2 + 1);
    save[n] = true;

    if (n % 2 == 0)
        return icarus(n / 2, save);
    return icarus(3 * n + 1, save);
}

int ackermann(int m, int n, std::vector<std::vector<int>> &save)
{
    if (m < save.size() && n < save[m].size() && save[m][n] > 0)
        return save[m][n];
    int retval;
    if (m == 0)
        retval = n + 1;
    else if (n == 0)
        retval = ackermann(m - 1, 1, save);
    else
        retval = ackermann(m - 1, ackermann(m, n - 1, save), save);
    if (m < save.size())
        save.resize(m * 2 + 1);
    if (n < save[m].size())
        save[m].resize(n * 2 + 1);
    save[m][n] = retval;
    return retval;
}

int ask_customer(const std::string &str, std::map<std::string, int> &memo)
{
    auto it = memo.find(str);
    if (it != memo.end())
        return it->second;

    int retval;
    std::cout << "What is your " << str << " :\n";
    std::cin >> retval;
    memo[str] = retval;
    return retval;
}
