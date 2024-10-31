import math


def sum(a, b):
    c = a + b
    print(c)
    return c

# sum(4, 5)

def sum_arr(arr):
    n = len(arr)
    s = 0
    for i in range(n):
        s = s + arr[i]
    print(s)
    return s

arr = [1,2,3, 4, 5]
# sum_arr(arr)

def isPalindrome(s):
    return "YES" if s == s[::-1] else "NO"


def fibonacci(n):
    fib = [0, 1]
    for i in range(2, n+1):
        fib.append(fib[i-1] + fib[i-2])
    return fib[n]

# 3. String Manipulation
# These questions deal with operations on strings, such as parsing, modifying, or analyzing the content.

# Example 3: "Palindrome Check"

# Problem: Given a string, check if it is a palindrome (i.e., it reads the same backward as forward).
# Input: A string s.
# Output: "YES" if it is a palindrome, otherwise "NO".

#===========CPP=============================
# #include <iostream>
# #include <string>
# using namespace std;

# string isPalindrome(string s) {
#     return (s == string(s.rbegin(), s.rend())) ? "YES" : "NO";
# }

# int main() {
#     string input;
#     cout << "Enter a string: ";
#     cin >> input;

#     cout << isPalindrome(input) << endl;
#     return 0;
# }


#=========================C#=========================
# static string IsPalindrome(string s)
#     {
#         char[] arr = s.ToCharArray();
#         Array.Reverse(arr);
#         string reversed = new string(arr);
#         return s == reversed ? "YES" : "NO";
#     }


# 6. Greedy Algorithms
# These problems require making the locally optimal choice at each step.

# Example 6: "Maximum Perimeter Triangle"

# Problem: Given an array of stick lengths, find the maximum perimeter of a triangle that can be formed using three sticks. If no triangle can be formed, return -1.
# Input: An array sticks[] of length n.
# Output: Maximum perimeter or -1.

def maxPerimeterTriangle(sticks):
    sticks.sort(reverse=True)
    for i in range(len(sticks) - 2):
        if sticks[i] < sticks[i+1] + sticks[i+2]:
            return sticks[i] + sticks[i+1] + sticks[i+2]
    return -1


# 7. Graph Algorithms
# Problems that require traversing or analyzing graphs.

# Example 7: "Breadth-First Search: Shortest Reach"

# Problem: Given an undirected graph and a starting node, find the shortest path from the starting node to all other nodes.
# Input: Graph representation and a starting node.
# Output: Shortest distance to each node from the starting node.

from collections import deque

def bfs_shortest_reach(n, edges, start):
    adj_list = {i: [] for i in range(1, n+1)}
    for u, v in edges:
        adj_list[u].append(v)
        adj_list[v].append(u)
    
    distances = [-1] * (n+1)
    distances[start] = 0
    queue = deque([start])
    
    while queue:
        node = queue.popleft()
        for neighbor in adj_list[node]:
            if distances[neighbor] == -1:
                distances[neighbor] = distances[node] + 6
                queue.append(neighbor)
    
    return [dist for i, dist in enumerate(distances) if i != start and i != 0]


# These problems often involve solving equations, manipulating numbers, or finding patterns.

# Example 8: "LCM of Two Numbers"

# Problem: Write a function to find the Least Common Multiple (LCM) of two integers.
# Input: Two integers a and b.
# Output: The LCM of a and b.

def lcm(a, b):
    return abs(a * b) // math.gcd(a, b)


# 9. Search Algorithms
# These questions require searching through data structures like arrays or trees.

# Example 9: "Binary Search"

# Problem: Implement a binary search algorithm to find the position of an element in a sorted array.
# Input: A sorted array arr[] and a target integer x.
# Output: The index of x in arr[] or -1 if not found.


def binarySearch(arr, x):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] < x:
            low = mid + 1
        else:
            high = mid - 1
    return -1

# 10. Bit Manipulation
# These problems often involve operations at the binary level.

# Example 10: "Lonely Integer"

# Problem: Given an array where every element appears twice except for one, find the element that appears only once.
# Input: An array arr[] of integers.
# Output: The integer that appears only once.

def lonelyInteger(arr):
    result = 0
    for num in arr:
        result ^= num
    return result
