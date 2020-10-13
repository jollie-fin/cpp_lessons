#include <queue>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <limits>
#include <map>
#include <string>

/* Dijkstra :
- Conditions :
  * No negative cost loop
  * Cost is fully deterministic
- Accept :
  * Any loosely connected graph
  * Non symetric cost
*/

struct Step
{
    int cumul_distance;
    int from;
    int to;

    bool operator<(const Step &other) const
    {
        return cumul_distance > other.cumul_distance;
    }
};

void dijkstra(int nb_nodes, int i, int j, auto compute_distance, auto neighbours)
{
    std::vector<int> cumul_distances(nb_nodes, std::numeric_limits<int>::max());
    std::vector<int> from(nb_nodes, -1);

    cumul_distances[i] = 0;

    std::priority_queue<Step> pq;
    pq.push(Step{0, -1, i});

    while (!pq.empty())
    {
        Step top = pq.top();
        pq.pop();

        if (top.cumul_distance > cumul_distances[top.to])
            continue;

        // After this line, this path is better than all the previous ones we found
        from[top.to] = top.from;
        cumul_distances[top.to] = top.cumul_distance;

        // Add all the neighbours
        for (auto k : neighbours(top.to))
        {
            int d = compute_distance(k, top.to);
            if (d == -1)
                continue;
            pq.push(Step{top.cumul_distance + d, top.to, k});
        }
    }

    // We are done ! Let's read the path

    int position = j;
    while (position != i)
    {
        std::cout << "Position = " << position << std::endl;
        position = from[position];
    }
    std::cout << "Position = " << position << std::endl;
}

struct CompareOldWay
{
    bool operator()(int a, int b)
    {
        return a * 2 < b;
    }
};

int main()
{
    int i, j;
    int nb_nodes;

    // std::cin >> i >> j;

    // std::less<int> compare_std;
    // std::cout << compare_std(i, j) << std::endl;

    // CompareOldWay compare_struct;
    // std::cout << compare_struct(i, j) << std::endl;

    // std::cout << "Enter coeff:" << std::endl;
    // int k = 2;

    // auto compare_lambda = [](int i, int j)
    //     {
    //         return k * i < j;
    //     };
    // std::cout << compare_lambda(i, j) << std::endl;
    // k = 1;
    // std::cout << compare_lambda(i, j) << std::endl;

    auto compute_distance = [](int i, int j)
    {
        if (i == j)
            return 1;
        if (i == 0 || j == 0)
            return -1;
        if (i % j == 0)
            return i / j;
        if (j % i == 0)
            return j / i;
        return -1;
    };

    auto neighbours = [&](int i)
    {
        std::vector<int> retval;
        for (int k = 1; k < nb_nodes; k++)
            if ((i % k == 0 || k % i == 0) && k != i)
                retval.emplace_back(k);
        return retval;
    };

    std::cout << "Max value + 1:" << std::endl;
    std::cin >> nb_nodes;
    std::cout << "Input i and j:" << std::endl;
    std::cin >> i >> j;
    dijkstra(nb_nodes, i, j, compute_distance, neighbours);
}
