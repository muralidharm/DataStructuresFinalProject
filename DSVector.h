/* The Vector Class
The Vector class should implement a standard contiguously-
allocated, sequential list of elements.
The class should be templated so it can hold any data type.
A Vector class should, at the very least, include a method
or methods for inserting elements, and an overloaded []
operator for element lookup by index. All vectors should
initially contain space for 10 elements and should grow at
a rate of 1.5 times each time the capacity is reached.
A graceful handling of out-of-bounds issues is expected.
*/

#ifndef VECTOR
#define VECTOR
#include <stdexcept>
#include<iostream>

using namespace std;

template<class T>
class Vector{

public:
    Vector();
    Vector(int);
    Vector(const Vector<T>&);

    void add(T);
    void add(T, int); //pushes elements back
    T get(int) const;
    int getLength();
    void set(int, T);
    int getEmpty();

    int size();
    void sort();
    void swap(int, int);
    void replace(const Vector<T>&);
    bool contains(T);

    T& operator[](const int);
    Vector<T>& operator=(const Vector<T>&);
    bool operator==(const Vector<T>& rhs);
    bool operator!=(const Vector<T>& rhs);
    bool operator<(const Vector<T>& rhs);
    Vector<T>& operator+=(T);
    void clear();

    ~Vector();

private:
    void resize();
    int length;
    int cap;
    T* list;
    int BASE_CAPACITY = 150;
};



template<class T>
Vector<T>::Vector()
{
    length=0;
    cap=BASE_CAPACITY;
    this->list=new T[cap];
}

template<class T>
Vector<T>::Vector(int digit)        //creates a Vector with capacity digit
{
    cap=digit;
    length=0;
    this->list=new T[cap];
}

template<class T>
Vector<T>::Vector(const Vector<T>& rhs)     //creates a Vector the same capacity and length as rhs containing same data in list
{
    cap = rhs.cap;
    length = rhs.length;
    this->list=new T[rhs.cap];
    for (int i = 0; i < length; i++)
    {
        list[ i ] = rhs.get(i);
    }
}

template<class T>
void Vector<T>::add(T rhs)      //adds rhs to end of the Vector, resizing if necessary
{
    if (length>=cap)
    {
        resize();
    }
    list[length]=rhs;
    length++;
}


template<class T>
void Vector<T>::add(T rhs, int index)   //adds rhs at index 'index' of the Vector, resizing and shiting data if necessary
{
    if (length==cap)
    {
        resize();
    }
    if (index<length and index >= 0)
    {
        for (int i=length; i>index; i--)
        {
            list[i]=list[i-1];
        }
        list[index]=rhs;
        length++;
    }
    else if (index==length)
    {
        list[index]=rhs;
        length++;
    }
    else                                        //greater than length
    {
        //throw std::out_of_range("Out of range"); AVOIDED USING std
        cerr << "Oops. Index is out of range" << endl;
    }
}


template<class T>
T Vector<T>::get(int index) const
{
    return list[index];
}

template<class T>
int Vector<T>::getLength()
{
    return length;
}

template<class T>
void Vector<T>::set(int index, T rhs)
{
    if (index>=length)
        return;
    list[index]=rhs;
}

template<class T>
int Vector<T>::size()
{
    return cap;
}

template<class T>
void Vector<T>::sort()              //sorts items in Vector ascendingly regarding of type
{
    T min;
    int count=size();
    for (int a=1; a<count; a++)
    {
        for (int b=count-1; b>=a; b--)
        {
            if (list[b-1] > list[b])
            {
                min = list[b-1];
                list[b-1] = list[b];
                list[b]=min;
            }
        }
    }
}

template<class T>
void Vector<T>::swap(int first, int second)
{
    T temp=list[first];
    list[first]=list[second];
    list[second]=temp;
}

template<class T>
T& Vector<T>::operator[](int index)
{
    if (index>=0 and index<cap)
    {
        return list[index];
    }
    else
    {
        cerr << "Oops. Can't go to index " << index << ". Needs to be 0..." << length << endl;
        return list[0];
    }

}

template<class T>
void Vector<T>::replace(const Vector<T>& rhs)
{
    if(&rhs != this) {  // Avoids copying yourself.
        delete[] list;
        length = rhs.length;
        cap = rhs.cap;
        list = new T[cap];
        for (int i=0; i<length; i++)
            list[i] = rhs.list[i];
    }
}

template<class T>
bool Vector<T>::contains(T rhs)
{
    for (int i=0; i<length; i++)
    {
        if (list[i]==rhs)
        {
            return true;
        }
    }
    return false;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
    if(&rhs != this) {  // Avoids copying yourself.
        delete[] list;
        length = rhs.length;
        cap = rhs.cap;
        list = new T[cap];
        for (int i=0; i<length; i++)
            list[i] = rhs.list[i];
    }
    return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& rhs)
{
    if (length != rhs.length)
        return false;
    for (int i=0; i<length; i++)
    {
        if (list[i]!=rhs.get(i))
        {
            return false;
        }
    }
    return true;
}


template<class T>
bool Vector<T>::operator!=(const Vector<T>& rhs)
{
    return !(operator==(rhs));
}

template<class T>
bool Vector<T>::operator<(const Vector<T>& rhs)
{
    bool solution = false;
    if (list[0] < rhs.list[0])
    {
        solution = true;
    }
    if (list[0] == rhs.list[0])
    {
        solution = (list[1]==rhs.list[1]);
    }
    return solution;
}

template<class T>
Vector<T>& Vector<T>::operator+=(T rhs)
{
    if (length==cap)
    {
        resize();
    }
    add(rhs);
    return *this;
}


template<class T>
int Vector<T>::getEmpty()
{
    return cap-length;
}

template<class T>
void Vector<T>::resize()
{
    int newCap=int(cap * 1.5);

    T* tempPtr = new T[newCap];
    for (int i=0; i<length; i++)
    {
        tempPtr[i] = list[i];
    }
    delete[] list;
    list = tempPtr;
    cap=newCap;
}

template<class T>
void Vector<T>::clear()
{
    for (int i=0; i<cap; i++)
    {
        list[i].clear();
    }
}

template<class T>
Vector<T>::~Vector()
{
    delete[] list;
}

#endif
