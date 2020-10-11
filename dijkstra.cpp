#include <queue>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <limits>

/* Dijkstra :
- Conditions :
  * No negative cost loop
  * Cost is fully deterministic
- Accept :
  * Any loosely connected graph
  * Non symetric cost
*/

int distance(int i, int j)
{
    if (i == 0 || j == 0 || i == j)
        return -1;
    if (i % j == 0)
        return i / j;
    if (j % i == 0)
        return j / i;
    return -1;
}

struct Node
{
    int cumul_distance;
    int from;
    int to;

    bool operator<(const Node &other) const
    {
        return cumul_distance > other.cumul_distance;
    }
};

void dijkstra(int max_int, int i, int j)
{
    assert(i < max_int);
    assert(j < max_int);
    assert(0 <= i);
    assert(0 <= j);
    
    std::vector<int> cumul_distances(max_int, std::numeric_limits<int>::max());
    std::vector<int> from(max_int, -1);

    cumul_distances[i] = 0;

    std::priority_queue<Node> pq;
    pq.push(Node{0, -1, i});

    while (!pq.empty() && from[j] == -1)
    {
        Node top = pq.top();
        pq.pop();

        if (top.cumul_distance > cumul_distances[top.to])
            continue;

        // After this line, this path is better than all the previous ones we found
        from[top.to] = top.from;
        cumul_distances[top.to] = top.cumul_distance;

        // Add all the neighbours
        for (int k = 0; k < max_int; k++)
        {
            int d = distance(k, top.to);
            if (d == -1)
                continue;
            pq.push(Node{top.cumul_distance + d, top.to, k});
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

int main()
{
    int i, j;
    int max_int;
    std::cout << "Max value:" << std::endl;
    std::cin >> max_int;
    std::cout << "Input i and j:" << std::endl;
    std::cin >> i >> j;
    dijkstra(max_int, i, j);
}
