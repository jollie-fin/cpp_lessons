#include <utility>
#include <iostream>
#include <array>
#include <opencv2/core.hpp>
#include <cstdint>

/*
    T(0) = 0
    T(1) = 0
    T(n) = 1 + T(n-1) + T(n-2)

    U(n) = T(n) - 1 forall n
    U(n) = U(n-1) + U(n-2) forall n>=2
    U(0) = -1
    U(1) = -1
*/


int64_t fibonacci_exp(int64_t n)
{
    if (n <= 1)
        return 1;
    return fibonacci_exp(n-1) + fibonacci_exp(n-2);
}

/*fibonacci_lin(n) -> Fn+1, Fn*/


/*
T(0) = 0
T(n) = 1 + T(n - 1)

*/
std::pair<int64_t, int64_t> fibonacci_lin(int64_t n)
{
    if (n <= 0)
        return {1,1};

    auto [next, prev] = fibonacci_lin(n - 1);
    return {next + prev, next};
}

/*fibonacci_lin(n) -> Fn+1, Fn*/
double fibonacci_lin_better(int64_t n, double next = 1, double prev = 1)
{
    if (n <= 0)
        return prev;

    return fibonacci_lin_better(n-1, prev + next, next);
}

/*Exponation rapide*/
auto pow(auto a, int64_t n, auto one)
{
    for (int64_t i = 0; i < n; i++)
        one *= a;
    return one;
}

auto fast_pow(auto a, int64_t n, auto one)
{
    if (n <= 0)
        return one;
    if (n % 2 == 1)
        return a * fast_pow(a, n-1, one);
    auto retval = fast_pow(a, n / 2, one);
    return retval * retval;
}

/*
Vn = Fn+1
     Fn

(1,1) Fn+1 = Fn+2
(1,0) Fn     Fn+1
  ^=A

A * Vn+1 = Vn

Vn = A^n * V0
*/

double fibonacci_log(int64_t n)
{
    cv::Matx<double,2,2> a(1,1,1,0);
    cv::Matx<double,2,2> retval = fast_pow(a, n, cv::Matx<double,2,2>::eye());
    cv::Matx<double,2,1> v(1,1);
    v = retval * v;
    return v(1);
}

double fibonacci_const(int64_t n)
{

}

int main()
{
    int64_t n;
    std::cin >> n;
    std::cout << "FastPow(" << n << ") = " << fast_pow(3,n,1) << std::endl;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci_log(n) << std::endl;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci_lin_better(n) << std::endl;
}