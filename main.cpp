#include "euclide.h"
#include "power.h"
#include "simple_numbers.h"
#include <chrono>
#include <math.h>
#include <set>
#include <bitset>

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

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

    std::cout << "euclide_gcd_algorithm_subtract: total time " << duration << " ms" << std::endl;

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

    std::cout << "euclide_gcd_algorithm_mod: total time " << duration << " ns" << std::endl;

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
    std::cout << "power_algorithms_iterations: total time " << duration << " ns" << std::endl;

    BOOST_CHECK_MESSAGE(result == 1024, "wrong result");
}

BOOST_AUTO_TEST_CASE(power_algorithms_power_of_two_with_post_multiplication)
{
    long base = 2;
    long baseForPostMultiplication = base;
    long power = 17;
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
    std::cout << "power_algorithms_power_of_two_with_post_multiplication: total time " << duration << " ns" << std::endl;

    BOOST_CHECK_MESSAGE(result == 131072, "wrong result");
}

BOOST_AUTO_TEST_CASE(power_algorithms_binary_representation)
{
    long base = 2;
    long power = 17;

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
    std::cout << "power_algorithms_binary_representation: total time " << duration << " ns" << std::endl;

    BOOST_CHECK_MESSAGE(res == 131072, "wrong result");
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
    quantity += 1; //because 1 is simple number too

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force: total time " << duration << " ms" << std::endl;
    std::cout << "quantity of simple numbers is " << quantity << std::endl;
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

        if(counter == 2)
            quantity++;

    }
    quantity += 1; //because 1 is simple number too

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chresultrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force_improved_sqrt: total time " << duration << " ms" << std::endl;
    std::cout << "quantity of simple numbers is " << quantity << std::endl;
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_brute_force_improved_sqrt_and_odd_only)
{
    long N = 10000;
    int quantity = 0;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        int counter = 0;
        for(int j = 1; j <= sqrt(i); j++)
        {
            if(i % 2 == 0)
                break;
            if(i % j == 0)
                counter++;
            if(counter > 2)
                break;
        }

        if(counter == 2)
            quantity++;

    }
    quantity += 1; //because 1 is simple number too

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force_improved_sqrt_and_odd_only: total time " << duration << " ms" << std::endl;
    std::cout << " quantity of simple numbers is " << quantity << std::endl;
}

BOOST_AUTO_TEST_CASE(simple_numbers_search_eratosphene)
{
    long N = 10000;
    int quantity = 0;
    std::bitset<10000> result;
    result.set();

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for(int i = 2; i < N; i++)
    {
        for(int j = static_cast<int>(pow(i, 2)); j <= N; j++)
        {
            if(j % i == 0)
                result.set(i);
        }

    }

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "\nsimple_numbers_search_brute_force_improved_sqrt_and_odd_only: total time " << duration << " ms" << std::endl;
    std::cout << " quantity of simple numbers is " << quantity << std::endl;
}
BOOST_AUTO_TEST_SUITE_END()
