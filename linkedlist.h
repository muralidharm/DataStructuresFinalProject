//My implementation of the Linked List Data Structure.
#ifndef LINKED_LIST
#define LINKED_LIST
template <class T>
class ListNode {
public:

private:
    ListNode<T>*next;
    ListNode<T>*previous;
    T data;
public:
    ListNode()
    {
        data = T();
        next = nullptr;
        previous = nullptr;
    }
    ListNode(T object)
    {
        data = object;
        next = nullptr;
        previous = nullptr;
    }
    template <class G> friend class LinkedList;
};


template<class T>
class LinkedList {

public:

    LinkedList()
    {
        head = nullptr;
        num_elements = 0;
    }
    LinkedList(T object)
    {
        head = new ListNode<T>(object);
        num_elements = 1;
    }

    LinkedList(const LinkedList<T>& otherList) : LinkedList()
    {
        if (!otherList.isEmpty())
        {

            ListNode<T>* otherNode = otherList.head;
            while (otherNode != nullptr)
            {
                add(otherNode->data);
                otherNode = otherNode->next;
            }
            num_elements = otherList.num_elements;

        }
    }

    void add(T object)
    {
        if (head == nullptr)
        {
            head = new ListNode<T>(object);
        }
        else
        {
            ListNode<T>* currentNode = head;
            ListNode<T>* temp = new ListNode<T>(object);
            while (currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
            }
            temp->previous = currentNode;
            currentNode->next = temp;

        }
        num_elements++;
    }
    void addToFront(T object)
    {
        if (head == nullptr)
        {
            head = new ListNode<T>(object);
        }
        else
        {
            ListNode<T>* temp = new ListNode<T>(object);
            temp->next = head;
            head->previous = temp;
            head = temp;
        }
        num_elements++;
    }
    void addAtIndex(T object, int index)
    {
        if (index == 0 || head == nullptr)
        {
            addToFront(object);
        }
        else
        {
            ListNode<T>* currentNode = head;
            int i = 0;
            for (i = 0; i < index-1 && currentNode != nullptr; i++)
            {
                currentNode = currentNode -> next;
            }
            if (i == index - 1)
            {
                ListNode<T>* temp = new ListNode<T> (object);
                temp -> previous = currentNode;
                temp -> next = currentNode->next;
                currentNode->next = temp;
                temp -> next -> previous = temp;
                num_elements++;
            }
            else
            {
                throw "Out of bounds.";
            }
        }
    }

    T get(int index)
    {
        return operator [](index);

    }
    int size()
    {
        return num_elements;
    }

    T remove(int index)
    {

        ListNode<T>* currentNode = head;
        T retrievedData;
        for (int i = 0; i < index && currentNode != nullptr; i++)
        {
            currentNode = currentNode->next;
        }
        if (currentNode == nullptr)
        {
            throw "Out of bounds.";
        }
        else
        {
            if (head == currentNode)
                head = currentNode->next;
            retrievedData = currentNode->data;
            if (currentNode->previous != nullptr)
                currentNode->previous->next = currentNode->next;
            if (currentNode->next != nullptr)
                currentNode->next->previous = currentNode->previous;
            delete currentNode;
            if (head == currentNode)
                head = nullptr;
            num_elements--;
        }
        return retrievedData;

    }

    bool isEmpty() const
    {
        //I personally don't believe that having an empty head is a good design, so checking the head
        //to see if it's null should be a sufficient emptiness check

        return (head == nullptr);
    }

    void clear()
    {
        if (head == nullptr)
        {
          //Do nothing!
        }
        else if (head->next == nullptr)
        {
            delete head;
        }
        else
        {
            ListNode<T>* temp;
            while (head != nullptr)
            {
                temp = head->next;
                delete head;
                head = temp;
            }
        }
        num_elements = 0;
    }

    ~LinkedList()
    {
       clear();
    }

    T& operator[] (int index)
    {
        ListNode<T>* currentNode = head;
        for (int i = 0; i < index && currentNode != nullptr; i++)
        {
            currentNode = currentNode->next;
        }
        if (currentNode == nullptr)
        {
            throw "Out of bounds.";
        }
        else
        {
            return currentNode->data;
        }
    }

    LinkedList<T>& operator=(LinkedList<T>& otherList)
    {
        if (!(this->isEmpty()))
        {
            clear();
        }
        if (!otherList.isEmpty())
        {

            ListNode<T>* otherNode = otherList.head;
            while (otherNode != nullptr)
            {
                add(otherNode->data);
                otherNode = otherNode->next;
            }

        }
        num_elements = otherList.num_elements;
        return *this;
    }
    //Uses a linear search method to see if an object is in the linked list.
    int contains(T object)
    {
        int length = size();
        for (int i = 0; i < length; i++)
        {
            T current = get(i);
            if (object == current)
            {
                return i;
            }
        }
        return -1;
    }

private:

    ListNode<T>*head;
    int num_elements;

};

#endif
