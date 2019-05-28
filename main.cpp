#include <chrono>
#include <math.h>
#include <set>
#include <bitset>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(euclide_gcd_algorithm_subtract)
{
    int a = 1234567890;
    int b = 12;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    while(a != b)
    {
        if(a > b)
            a-= b;
        else
            b-=a;
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    std::cout << "\neuclide_gcd_algorithm_subtract: total time " << duration << " ns (1234567890 and 12)" << std::endl;

    BOOST_CHECK_MESSAGE(a == 6, "wrong result");
}

BOOST_AUTO_TEST_CASE(euclide_gcd_algorithm_mod)
{
    int a = 1234567890;
    int b = 12;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    while(a != 0 && b != 0)
    {
        if(a > b)
            a %= b;
        else
            b %= a;
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "\neuclide_gcd_algorithm_mod: total time " << duration << " ns (1234567890 and 12)" << std::endl;

    BOOST_CHECK_MESSAGE(a == 6, "wrong result");
}

BOOST_AUTO_TEST_CASE(power_algorithms_iterations)
{
    int base = 2;
    int power = 10;
    int result = 1;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    while(power)
    {
        result*=base;
        power--;
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    std::cout << "\npower_algorithms_iterations: total time " << duration << " ns (2^10)" << std::endl;

    BOOST_CHECK_MESSAGE(result == 1024, "wrong result");
}

bool VerifyNumberIsPowerOfTwo(long value, int& power)
{
    if(value <= 0)
        return false;

    while((value % 2)==0)
    {
        power++;
        if((value /=2 ) == 1)
            return true;
    }

    power = 0;
    return false;
}
BOOST_AUTO_TEST_CASE(power_algorithms_power_of_two_with_post_multiplication)
{
    long base = 2;
    long baseForPostMultiplication = base;
    long power = 10;
    long binaryPower = power;
    int steps;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    while(!VerifyNumberIsPowerOfTwo(binaryPower, steps))
        binaryPower--;

    for(int i = 0; i < steps; i++)
        base *= base;

    long diff = power - binaryPower;
    long result = base;

    while(diff)
    {
        result*=baseForPostMultiplication;
        diff--;
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    std::cout << "\npower_algorithms_power_of_two_with_post_multiplication: total time " << duration <<" ns (2^10)" << std::endl;

    BOOST_CHECK_MESSAGE(result == 1024, "wrong result");
}

BOOST_AUTO_TEST_CASE(power_algorithms_binary_representation)
{
    long base = 2;
    long power = 10;

    long res = 1;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    while(power > 1)
    {
        if(power % 2 == 1)
            res *= base;
        base *= base;
        power /= 2;
    }

    if(power > 0)
        res *= base;

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    std::cout << "\npower_algorithms_binary_representation: total time " << duration << " ns (2^10)" << std::endl;

    BOOST_CHECK_MESSAGE(res == 1024, "wrong result");
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_brute_force)
{
    long N = 10000;
    int quantity = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        int counter = 0;
        for(int j = 1; j <= i; j++)
        {
            if(i % j == 0)
                counter++;
            if(counter > 2)
                break;
        }

        if(counter == 2)
            quantity++;
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force: total time " << duration << " ms" << std::endl;
    std::cout << "quantity of simple numbers is " << quantity << " out of " << N << std::endl;
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_brute_force_improved_sqrt)
{
    long N = 10000;
    int quantity = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        int counter = 0;
        for(int j = 1; j <= sqrt(i); j++)
        {
            if(i % j == 0)
                counter++;
            if(counter > 2)
                break;
        }

        if(counter == 1)
            quantity++;
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force_improved_sqrt: total time " << duration << " ms" << std::endl;
    std::cout << "quantity of simple numbers is " << quantity << " out of " << N <<std::endl;
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_brute_force_improved_sqrt_and_odd_only)
{
    long N = 10000;
    int quantity = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        if(i % 2 == 0 && i != 2)
            continue;

        int counter = 0;
        for(int j = 1; j <= sqrt(i); j++)
        {
            if(i % j == 0)
                counter++;
            if(counter > 2)
                break;
        }

        if(counter == 1)
            quantity++;

    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force_improved_sqrt_and_odd_only: total time " << duration << " ms" << std::endl;
    std::cout << " quantity of simple numbers is " << quantity << " out of " << N << std::endl;
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_eratosphene)
{
    constexpr int N = 10000;
    std::bitset<N> result;
    result.set();
    //Since 0 and 1 are not simple numbers
    result.set(0, false);
    result.set(1, false);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        int startNumber = static_cast<int>(pow(i, 2));
        if(startNumber > N)
            break;

        if(result[static_cast<size_t>(i)] == 0)
            continue;

        for(int j = startNumber; j < N; j++)
        {
            if(j % i == 0)
                result.set(static_cast<size_t>(j), false);
        }
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_eratosphene: total time " << duration << " us" << std::endl;
    std::cout << " quantity of simple numbers is " << result.count() << " out of " << N << std::endl;
}

int F(int n)
{
    if(n < 2)
        return n;
    else
        return F(n - 1) + F(n - 2);
}

BOOST_AUTO_TEST_CASE(fibonachi_numbers_search_recursion)
{

    constexpr int N = 10;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    auto n = F(N);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
    std::cout << "\nfibonachi_numbers_search_recursion: total time " << duration << " ns" << std::endl;
    std::cout << " fibonachi numbers is " << n << " (" << N << "th Fibonachi number)" << std::endl;
}

BOOST_AUTO_TEST_CASE(fibonachi_numbers_search_iterations)
{
    long double a = 1;
    long double b = 1;
    long double f = 0;
    constexpr int N = 1200;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 3; i <= N; i++)
    {
        f = a + b;
        a = b;
        b = f;
    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\nfibonachi_numbers_search_iterations: total time " << duration << " us" << std::endl;
    std::cout << " fibonachi numbers is " << f <<  " (" << N << "th Fibonachi number)" << std::endl;
}

BOOST_AUTO_TEST_CASE(fibonachi_numbers_search_golden_cut)
{
    double fi = 1.6180339887498948482045868343656;
    constexpr int N = 1200;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    auto result = pow(fi, N)/sqrt(5) + 0.5;

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "\nfibonachi_numbers_search_golden_cut : total time " << duration << " us" << std::endl;
    std::cout << " fibonachi numbers is " << result << " (" << N << "th Fibonachi number)" << std::endl;
}
BOOST_AUTO_TEST_SUITE_END()
