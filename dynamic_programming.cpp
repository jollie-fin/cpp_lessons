#include <string>
#include <algorithm>
#include <utility>

/* O((nm)^(n+m)) */
int levenshtein_brut(std::string_view str1, std::string_view str2)
{
    int retval = str1.size() + str2.size();
    if (str1.empty())
        return str2.size();
    if (str2.empty())
        return str1.size();
    if (str1 == str2)
        return 0;
    for (int pos = 0; pos != str1.size(); pos++)
    {
        // str1[0:pos] + str1[pos+1:]
        std::string newstr1 =
            std::string(str1.substr(0, pos)) +
            std::string(str1.substr(pos + 1));
        retval = std::min(retval, levenshtein_brut(newstr1, str2)) + 1;
    }

    for (int pos = 0; pos != str2.size(); pos++)
    {
        std::string newstr2 =
            std::string(str2.substr(0, pos)) +
            std::string(str2.substr(pos + 1));
        retval = std::min(retval, levenshtein_brut(str1, newstr2)) + 1;
    }

    for (int pos1 = 0; pos1 != str1.size(); pos1++)
        for (int pos2 = 0; pos2 != str2.size(); pos2++)
        {
            std::string newstr1 =
                std::string(str1.substr(0, pos1)) +
                std::string(str1.substr(pos2 + 1));
            std::string newstr2 =
                std::string(str2.substr(0, pos2)) +
                std::string(str2.substr(pos2 + 1));
            retval = std::min(retval, levenshtein_brut(newstr1, newstr2)) + 1;
        }
    return retval;
}

/* O(nm), memory : O(nm) */
int levenshtein_dynamic(std::string_view str1, std::string_view str2)
{
    int max_cost = str1.size() + str2.size();

    //cost[i][j] = levenshtein(str1[:i], str2[:j])
    std::vector<std::vector<int>> cost(
        str1.size() + 1,
        std::vector<int>(
            str2.size() + 1,
            max_cost));

    for (int pos = 0; pos <= str1.size(); pos++)
        cost[pos][0] = pos;

    for (int pos = 0; pos <= str2.size(); pos++)
        cost[0][pos] = pos;

    // Compute cost[i+1][j+1]
    for (int i = 0; i != str1.size(); i++)
    {
        for (int j = 0; j != str2.size(); j++)
        {
            int substitution_cost = 1;
            if (str1[i] == str2[j])
                substitution_cost = 0;

            cost[i+1][j+1] =
                std::min(
                    std::min(
                        1 + cost[i][j+1],
                        1 + cost[i+1][j]
                    ),
                    substitution_cost + cost[i][j]
                );
        }
    }
    return cost.back().back();
}

/* O(nm), O(min(n,m)) */
int levenshtein_dynamic_better(std::string_view str1, std::string_view str2)
{
    if (str2.size() > str1.size())
        return levenshtein_dynamic_better(str2, str1);

    int max_cost = str1.size() + str2.size();

    //cost[i][j] = levenshtein(str1[:i], str2[:j])
    std::vector<std::vector<int>> cost(
        2,
        std::vector<int>(
            str2.size() + 1,
            max_cost));

    for (int pos = 0; pos <= str2.size(); pos++)
        cost[0][pos] = pos;

    // Compute cost[i+1][j+1]
    for (int i = 0; i != str1.size(); i++)
    {
        cost[1][0] = i + 1;
        for (int j = 0; j != str2.size(); j++)
        {
            int substitution_cost = 1;
            if (str1[i] == str2[j])
                substitution_cost = 0;

            cost[1][j+1] =
                std::min(
                    std::min(
                        1 + cost[0][j+1],
                        1 + cost[1][j]
                    ),
                    substitution_cost + cost[0][j]
                );
        }
        std::swap(cost[0], cost[1]);
    }
    return cost[0].back();
}


/* cf automatic new line */


/*
  core0
  core1

  15 min, 10 min, 9 min, 8 min, 8 min
    
c/w 5 4 3 2 2
0   T T T T T T
1              
2           T T
3         T T T
4       T T T T
5     T T T T T
6           T T
7         T T T
8         T T T

*/

bool cargo(const std::vector<int> &weights)
{
    int sum_weight = 0;
    for (auto weight : weights)
        sum_weight += weight;

    if (sum_weight % 2 != 0)
        return false;

    /* best[w][c] = true <=> \exists s \in weights[0:w] tq sum(s) = c */
    std::vector<std::vector<bool>> partial_weight(
        weights.size() + 1,
        std::vector<bool>(
            sum_weight));

    partial_weight[0][0] = true;
    for (int w = 0; w != weights.size(); w++)
    {
        for (int c = 0; c != sum_weight; c++)
        {
            if (partial_weight[w][c])
            {
                partial_weight[w + 1][c] = true;

                if (c + weights[w] < partial_weight.front().size())
                    partial_weight[w + 1][c + weights[w]] = true;
            }
        }
    }

    return partial_weight.back()[sum_weight/2];
}



/*Problem 1*/
void startup(const std::vector<int> &values)
{

}

/* sum(values[i], values[i+1] ... values[j-1]) */
/* O(1) */
int sum_partial(int i, int j)
{

}


/*Problem 1.1*/
void startup(const std::vector<std::vector<int>> &values)
{

}

/* sum(sub_matrix) */
/* O(1) */
int sum_partial(int i1, int j1, int i2, int j2)
{

}



/* Problem 2 */
int nb_lines(std::vector<int> word_length, int line_witdth)
{

}

/*min(sum(de ce qui reste à la fin de chaque ligne^2))*/
int optimum_repartition(std::vector<int> word_length, int line_witdth)
{

}
