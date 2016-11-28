#ifndef STACK
#define STACK

#include "linkedlist.h"

template<class T>
class Stack{

    public:

        T pop()
        {
            return data.remove(data.size()-1);
        }

        T peek()
        {
            return data.get(data.size()-1);
        }
        void push(T object)
        {
            data.add(object);
        }
        bool isEmpty()
        {
            return data.isEmpty();
        }
        bool contains(T object)
        {
            return (data.contains(object) != -1);
        }
        int size()
        {
            return data.size();
        }

        LinkedList<T> toList()
        {
            return data;
        }


    private:

        LinkedList<T> data;

};

#endif
