#include <cstdint>
#include <vector>
#include <queue>
#include <iostream>

/*

a b c
d e f

a b c d e f



48 = 0b00110000

T =
a0 a1 a2 a3
b0 b1 b2 b3
c0 c1 c2 c3
d0 d1 d2 d3

T = T ^ 1 : flip a0
T = T ^ 8 : flip a3
T = T ^ (1 << 3) : flip a3

T = T ^ 0b1111 : flip a
T = T ^ (0b1111 << 4) : flip a

T = T ^ (0b0001000100010001) : flip 0

l = (T & (0b1111 << 4)) >> 4
carry = l & 1
l = l >> 1
l = l | (carry << 3)
T = T & ~(0b1111 << 4)
T = T | (l << 4) // rotate to the left b

*/

uint32_t flip(uint32_t board, int pos)
{
    return board ^ (1 << pos);
}

uint32_t flip_row(uint32_t board, int row)
{
    return board ^ (0b1111 << (row * 4));
}

uint32_t flip_col(uint32_t board, int col)
{
    return board ^ (0x1111 << col);
}

uint32_t rotate_row(uint32_t board, int row)
{
    uint32_t l = board & (0b1111 << (row * 4));
    l = l >> (row * 4);
    uint32_t carry = l & 0b0001;
    l = l >> 1;
    l = l | (carry << 3);
    board = board & ~(0b1111 << (row * 4));
    board = board | (l << (row * 4));
    return board;
}

uint32_t rotate_col(uint32_t board, int col)
{
    uint32_t l = board & (0x1111 << col);
    l = l >> col;
    uint32_t carry = l & 0x0001;
    l = l >> 4;
    l = l | (carry << (4*3));
    board = board & ~(0x1111 << col);
    board = board | (l << col);
    return board;
}

void propagate(std::vector<int> &best, uint32_t board, int value)
{
    for (int pos = 0; pos < 16; pos++)
    {
        uint32_t neigh = flip(board, pos);
        if (best[neigh] > value)
            best[neigh] = value;
    }
    for (int pos = 0; pos < 4; pos++)
    {
        uint32_t neigh;
        neigh = flip_col(board, pos);
        if (best[neigh] > value)
            best[neigh] = value;
        neigh = flip_row(board, pos);
        if (best[neigh] > value)
            best[neigh] = value;
        neigh = rotate_col(board, pos);
        if (best[neigh] > value)
            best[neigh] = value;
        neigh = rotate_row(board, pos);
        if (best[neigh] > value)
            best[neigh] = value;
    }
}

std::vector<int> neighbours(uint32_t board)
{
    std::vector<int> retval;
    for (int pos = 0; pos < 16; pos++)
        retval.emplace_back(flip(board, pos));

    for (int pos = 0; pos < 4; pos++)
    {
        retval.emplace_back(flip_col(board, pos));
        retval.emplace_back(flip_row(board, pos));
        retval.emplace_back(rotate_col(board, pos));
        retval.emplace_back(rotate_row(board, pos));
    }
    return retval;
}

int solve(uint32_t init)
{
    std::vector<int> best(1 << 16, 17);
    best[init] = 0;
    int d = 0;
    while (best[0xFFFF] == 17) // while(!queue.empty() && from[0xFFFF] == -1)
    {
        for (uint32_t board = 0; board < (1 << 16); board++) // pop multiple times
            if (best[board] == d)                            // ^^^^^^^^^^^^^^^^^^
                propagate(best, board, d + 1); // for neigh
        d++;
    }
    return best[0xFFFF];
}

int solve_queue(uint32_t init)
{
    std::vector<int> best(1 << 16, 17);
    best[init] = 0;
    std::queue<uint32_t> queue;
    queue.push(init);
    while (!queue.empty() && best[0xFFFF] == 17)
    {
        uint32_t board = queue.front();
        queue.pop();

        for (auto neigh : neighbours(board))
        {
            if (best[neigh] != 17)
                continue;
            best[neigh] = best[board] + 1;
            queue.push(neigh);
        }
    }
    return best[0xFFFF];
}

/*

XXXXX

XXXX
X

XXX
X
X

...

3*4*5 = 60 < 64

*/

int main()
{
    uint32_t board = 0;
    std::cin >> std::hex >> board;
    std::cout << solve_queue(board) << std::endl;
}
