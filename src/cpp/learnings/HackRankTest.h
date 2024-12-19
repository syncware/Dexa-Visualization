#pragma once

#ifndef HACKRANKTEST_H
#define HACKRANKTEST_H
#endif

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HackRankTest
{

public:
    string isPalindrome(string s);
    void sortIntegers(vector<int> &vec, bool isAscending);
    int fibonacci(int n);
    int maxPerimeterTriangle(vector<int> &sticks);
    int binarySearch(vector<int> &arrr, int x);
};

string HackRankTest::isPalindrome(string s)
{
    string sReversed = s;
    int n = s.length();
    int j = -1;

    for (int i = n - 1; i >= 0; i--)
    {
        j++;
        sReversed[j] = s[i];
    }

    if (s == sReversed)
    {
        return "YES";
    }
    else
    {
        return "NO";
    }
}

void HackRankTest::sortIntegers(vector<int> &vec, bool isAscending)
{

    int temp;
    int n = vec.size();

    for (int j = 0; j <= n - 2; j++)
    {
        for (int i = 0; i <= n - 2; i++)
        {
            if (isAscending)
            {
                if (vec[i] > vec[i + 1])
                {
                    temp = vec[i + 1];
                    vec[i + 1] = vec[i];
                    vec[i] = temp;
                }
            }
            else
            {

                if (vec[i] < vec[i + 1])
                {
                    temp = vec[i + 1];
                    vec[i + 1] = vec[i];
                    vec[i] = temp;
                }
            }
        }
    }
}

int HackRankTest::fibonacci(int n)
{
    vector<int> fb;
    fb.push_back(0);
    fb.push_back(1);

    for (int i = 2; i <= n; i++)
    {
        int ans = fb[i - 2] + fb[i - 1];
        fb.push_back(ans);
    }

    return fb[n];
}

// def maxPerimeterTriangle(sticks):
//     sticks.sort(reverse=True)
//     for i in range(len(sticks) - 2):
//         if sticks[i] < sticks[i+1] + sticks[i+2]:
//             return sticks[i] + sticks[i+1] + sticks[i+2]
//     return -1

int HackRankTest::maxPerimeterTriangle(vector<int> &sticks)
{
    bool isAscending = false;
    sortIntegers(sticks, isAscending);

    int n = sticks.size();
    for (int i = 0; i < n - 2; i++)
    {
        if (sticks[i] < sticks[i + 1] + sticks[i + 2])
        {
            return sticks[i] + sticks[i + 1] + sticks[i + 2];
        }
    }

    return -1;
}

int HackRankTest::binarySearch(vector<int> &arr, int x)
{
    bool isAscending = false;
    sortIntegers(arr, isAscending);

    int n = arr.size();

    int low = 0;
    int high = n - 1;
    int mid = low;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

// LCM

// import math

// def lcm(a, b):
//     return abs(a * b) // math.gcd(a, b)