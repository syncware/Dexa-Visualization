#pragma once

#ifndef STACK_H
#define STACK_H
#endif

#include <iostream>

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int size) : capacity(size), top(-1) {
        arr = new int[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int val) {
        if (top == capacity - 1) {
            std::cout << "Stack Overflow" << std::endl;
            return;
        }
        arr[++top] = val;
    }

    void pop() {
        if (top == -1) {
            std::cout << "Stack Underflow" << std::endl;
            return;
        }
        --top;
    }

    int peek() const {
        if (top == -1) {
            std::cout << "Stack is empty" << std::endl;
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

    void display() const {
        for (int i = 0; i <= top; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};


class StackDouble {
    private:
        double* arr;
        int top;
        int capacity;
    
    public:
        StackDouble(int size): capacity(size), top(-1) {
            //capacity = size;
            //top = -1;
            arr = new double[capacity];
        }

        ~StackDouble() {
            delete []arr;
        }

        void push(double x) {
            if(top == capacity - 1) {
                std::cout << "Index out of range";
                return;
            }

            arr[++top] = x;
        }

        void pop() {
            if(top == -1){
                std::cout << "The stack is empty";
                return;
            }

            --top;
        }

        double peek() const {
            if(top == -1){
                std::cout << "The stack is empty";
                return -1;
            }

            return arr[top];
        }

        bool isEmpty() const{
            return top == -1;
        }

        void display() const {
            for(int i = 0; i <= top; i++){
                std::cout << arr[i] << " ";
            }

            std::cout << std::endl;
        }
};