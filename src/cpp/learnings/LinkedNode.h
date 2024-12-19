#pragma once

#ifndef LINKEDNODE_H
#define LINKEDNODE_H
#endif

#include <iostream>

class LinkedNode
{
public:
    int data;
    LinkedNode *next;

    LinkedNode(int val)
    {
        data = val;
        next = nullptr;
    }
};