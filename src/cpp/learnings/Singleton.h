#pragma once

#ifndef SINGLETON_H
#define SINGLETON_H
#endif

class Singleton
{
private:
    static Singleton *instance;
    int value;

    // Private constructor prevents instantiation
    Singleton()
    {
        value = 0;
    }

public:
    // Delete copy constructor and assign operator
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static Singleton *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }

        return instance;
    }

    void setValue(int val)
    {
        value = val;
    }

    int getValue() const
    {
        return value;
    }
};

Singleton *Singleton::instance = nullptr;
