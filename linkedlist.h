#ifndef LINKED_LIST
#define LINKED_LIST
#include <fstream>

template <class T>
class ListNode {
template <class U> friend class LinkedList;
public:

    ListNode();
    ListNode(T);
    friend class templateList;
    void printToTerminal();
    ListNode<T>* getNext();
    ListNode<T>* getPrevious();
    T& getData();
    void setNext(ListNode<T>*);
    void setPrevious(ListNode<T>*);
    void setData(T);
    bool operator== (ListNode<T>) const;
    ~ListNode();


private:
    ListNode<T>* next;
    ListNode<T>* previous;
    T data;
};


template<class T>
class LinkedList {

public:

    LinkedList();
    LinkedList(T);
    LinkedList(const LinkedList<T>&);

    void add(T);
    void addToFront(T);
    T get(int);
    ListNode<T>* getFront() const;
    ListNode<T>* getBack();
    int size();
    void setBack(ListNode<T>*);
    void setFront(ListNode<T>*);
    bool contains(T);                   //returns true if list contains T
    T remove(int);
    int find(T);
    bool isEmpty();                     //returns true if list is empty (size=0)
    void clear();                       //clears all data from list
    LinkedList<T>& replace(LinkedList<T>&);

    ~LinkedList();


    T& operator[] (int);
    LinkedList<T>& operator=(LinkedList<T>&);
    bool operator== (LinkedList<T> rhs) const;

private:

    ListNode<T>* front;
    ListNode<T>* back;
    int numElements;

};





//Implementation for ListNode

template<class T>
ListNode<T>::ListNode()
{
   next=nullptr;
   previous=nullptr;
   //data=T();
}

template<class T>
ListNode<T>::ListNode(T rhs)
{
   next=nullptr;
   previous=nullptr;
   data=rhs;
}

template<class T>
T& ListNode<T>::getData()
{
    return data;
}

template<class T>
ListNode<T>* ListNode<T>::getNext()
{
    return next;
}

template<class T>
ListNode<T>* ListNode<T>::getPrevious()
{
    return previous;
}


template<class T>
void ListNode<T>::setNext(ListNode<T>* rhs)
{
    next=rhs->getNext();
}

template<class T>
void ListNode<T>::setPrevious(ListNode<T>* rhs)
{
    previous=rhs->getPrevious();
}

template<class T>
void ListNode<T>::setData(T rhs)
{
    data=rhs;
}


template<class T>
bool ListNode<T>::operator== (ListNode<T> rhs) const
{
    bool isSame=false;
    T rhsData=rhs.getData();
    if (data==rhsData)
        isSame=true;
    return isSame;
}


template<class T>
ListNode<T>::~ListNode()
{
    //delete data;
}





//Implementation for LinkedList
template<class T>
LinkedList<T>::LinkedList()
{
   front=nullptr;
   back=nullptr;
   numElements=0;
}


template<class T>
LinkedList<T>::LinkedList(T rhs)
{
   ListNode<T>* addedRhs = new ListNode<T>(rhs);
   front=addedRhs;
   back=addedRhs;
   numElements=1;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs) : LinkedList()
{

   for (ListNode<T>* posInRHS = rhs.getFront(); posInRHS != nullptr; posInRHS = posInRHS->getNext() )
   {
       add(posInRHS->getData());
   }
}

template<class T>
int LinkedList<T>::size()
{
   return numElements;
}

template<class T>
ListNode<T>* LinkedList<T>::getFront() const
{
   return front;
}

template<class T>
ListNode<T>* LinkedList<T>::getBack()
{
   return back;
}

template<class T>
void LinkedList<T>::setBack(ListNode<T>* rhs)
{
    back=rhs->getBack();
}

template<class T>
void LinkedList<T>::setFront(ListNode<T>* rhs)
{
    front=rhs->getFront();
}

template<class T>
void LinkedList<T>::add(T rhs)
{
  if (front==nullptr)
  {
    front = new ListNode<T>(rhs);
    back = front;
  }
  else
  {
     ListNode<T>* cur = back;
     ListNode<T>* newNode = new  ListNode<T>(rhs);
     back->next = newNode;
     newNode->previous=cur;
     back=newNode;
  }
  numElements++;
}

template<class T>
void LinkedList<T>::addToFront(T rhs)
{
    if (front==nullptr)
    {
      front = new ListNode<T>(rhs);
      back = front;
    }
    else
    {
        ListNode<T>* cur = front;
        ListNode<T>* newNode = new  ListNode<T>(rhs);
        front->previous = newNode;
        newNode->next=cur;
        front=newNode;
    }
    numElements++;
}


template<class T>
T LinkedList<T>::remove(int index)
{
    T valueDeleted;
    ListNode<T>* current=front;

    if (index < 0 or index >= size()) {
        throw "Index out of bounds!";
    } // Now the index must be valid.
    // Advance current to the right place
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    // Fix the pointers.
    if (current == front and current == back) {
        front = back = nullptr;
    }
    else if (current == front) {
        front = front->next;
        front->previous = nullptr;
    }
    else if (current == back) {
        back = back->previous;
        back->next = nullptr;
    }
    else {
        current->next->previous = current->previous;
        current->previous->next = current->next;
    }
    // Now the list is pointed around current, no matter what.
    valueDeleted = current->data;
    delete current;
    numElements--;
    return valueDeleted;
}

template <class T>
bool LinkedList<T>::isEmpty()
{
    if (numElements==0)
        return true;
    else
        return false;
}

template<class T>
bool LinkedList<T>::operator== (LinkedList<T> rhs) const
{
   if (numElements!=rhs.size())
       return false;
   for (ListNode<T>* myPosition = front, *rhsPosition = rhs.getFront();
        myPosition != nullptr; myPosition = myPosition->getNext(), rhsPosition = rhsPosition->getNext()) {
        if (myPosition->getData() != rhsPosition->getData())
            return false;
   }
   return true;
}

template <class T>
LinkedList<T>& LinkedList<T>::replace(LinkedList<T>& rhs)
{
    if (this == &rhs)
        return *this;
    clear();
    for (ListNode<T>* posInRHS = rhs.getFront(); posInRHS != nullptr; posInRHS = posInRHS->getNext() )
    {
        add(posInRHS->getData());
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& rhs)
{
    if (this == &rhs)
        return *this;
    clear();
    for (ListNode<T>* posInRHS = rhs.getFront(); posInRHS != nullptr; posInRHS = posInRHS->getNext() )
    {
        add(posInRHS->getData());
    }
    return *this;
}


template <class T>
T LinkedList<T>::get(int index)
{
    return (*this)[index];
}

template <class T>
T& LinkedList<T>::operator[] (int index)
{
    ListNode<T>* cur = front;
    if (index==0 && cur != nullptr)
    {
        return cur->getData();
    }
    else
    {
        for (int i=0; i < index && cur != nullptr; i++)
        {
            cur=cur->next;    //cur will not seg fault since the loop will not execute if cur==nullptr
        }
        if (cur==nullptr)
            throw "Index too big!";
        else
            return cur->getData();
     }
}

template<class T>
bool LinkedList<T>::contains(T rhs)
{
    for (int i=0; i<size(); i++)
    {
        if ((*this)[i]==rhs)
        {
            return true;
        }
    }
    return false;
}

template<class T>
int LinkedList<T>::find(T rhs)
{
    for (int i=0; i<size(); i++)
    {
        if ((*this)[i]==rhs)
        {
            return i;
        }
    }
    return -1;
}

template<class T>
void LinkedList<T>::clear()
{
    ListNode<T> *current = front;
    while (current != nullptr) {
        ListNode<T> *next = current->next;
        delete current;
        current = next;
    }
    front = back = nullptr;
}

template<class T>
LinkedList<T>:: ~LinkedList()
{
    clear();
}

#endif
