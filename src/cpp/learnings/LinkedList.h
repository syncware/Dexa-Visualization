#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#endif

#include <iostream>
#include "LinkedNode.h"

class LinkedList
{
private:
    LinkedNode *head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    // Insert at the beginning
    void insert(int val)
    {
        LinkedNode *newNode = new LinkedNode(val);
        newNode->next = head;
        head = newNode;
    }

    // Delete a node by value
    void remove(int val)
    {
        if (head == nullptr)
            return;

        if (head->data == val)
        {
            LinkedNode *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        LinkedNode *current = head;
        while (current->next != nullptr &&
               current->next->data != val)
        {
            current = current->next;
        }

        if (current->next != nullptr)
        {
            LinkedNode *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Print the list
    void display()
    {
        LinkedNode *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " ->";
            temp = temp->next;
        }

        std::cout << "NULL" << std::endl;
    }
};