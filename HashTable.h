#ifndef HASHTABLE
#define HASHTABLE

#include "LinkedList.h"
#include "DSVector.h"
#include "DSString.h"

using namespace std;
const int TABLE_SIZE = 150;
int counter = 0;


//Header for HashNode
template <class K, class V>
class HashNode {
public:
    HashNode(K key, V value) {

        this->key = key;

        this->value = value;

    }
    HashNode();
    K getKey() const;
    V getValue() const;
    void setValue(V value);

private:
    K key;
    V value;
};

//Header for HashTable
template <class K, class V>
class HashTable{

    public:
        HashTable();
        LinkedList<HashNode<K,V>> getTable();
        int hashFunc(String);
        int hashFunc(int);
        void addNode(HashNode<K,V>);
        void addNode(K, V);
        bool contains(HashNode<K,V>);          //returns true if HashNode is in list
        HashNode<K,V>& get(HashNode<K,V>);          //returns HashNode if it exists
        int size();
        void clear();
        LinkedList<HashNode<K,V>>& returnList(K rhs);
        HashNode<K,V>& returnNode(V rhs);

        HashNode<K,V>& operator[] (int);

        ~HashTable();

    private:
        HashTable(HashTable&);
        Vector<LinkedList<HashNode<K,V>>> nodes;

};

//Implementation for HashNode

template <class K, class V>
HashNode<K,V>::HashNode()
{
}

template <class K, class V>
K HashNode<K,V>::getKey() const
{
    return key;
}

template <class K, class V>
V HashNode<K,V>::getValue() const
{
    return value;
}

template <class K, class V>
void HashNode<K,V>::setValue(V rhs)
{
    value=rhs;
}

//Implementation for HashTable
template <class K, class V>
HashTable<K,V>::HashTable()
{

}

//WRONG
template <class K, class V>
HashTable<K,V>::HashTable(HashTable<K,V>& rhs)        //copy constructor
{
    nodes.clear();
    /*for (int i=0; i<rhs.getTable().size(); i++)
    {
         nodes.add(rhs.getTable().get(i));
    }*/
}

template <class K, class V>
int HashTable<K,V>::hashFunc(int k)              //assumes int key
{
    int size = TABLE_SIZE;
    return (k%size);
}

template <class K, class V>
int HashTable<K,V>::hashFunc(String k)              //assumes String key, uses size
{
    int kSize = k.size();
    int size = TABLE_SIZE;
    return (kSize%size);
}

template <class K, class V>
void HashTable<K,V>::addNode(HashNode<K, V> entry)
{
    int rhsK = entry.getKey();
    int hashValue = hashFunc(rhsK);
    nodes[hashValue].add(entry);
    counter++;
}

template <class K, class V>
void HashTable<K,V>::addNode(K key, V value)
{
    HashNode<K,V> entry(key, value);
    K rhsK = entry.getKey();
    int hashValue = hashFunc(rhsK);
    nodes[hashValue].add(entry);
    counter++;
}


template <class K, class V>
LinkedList<HashNode<K,V>>& HashTable<K,V>::returnList(K rhs)
{
    for (int i=0; i<nodes.size(); i++)
    {
        if (nodes[i].get(0).getKey()==rhs)
            return nodes[i];
    }
}

template <class K, class V>
HashNode<K,V>& HashTable<K,V>::returnNode(V rhs)
{
    for (int i=0; i<nodes.size(); i++)
    {
        for (int j=0; j<nodes[i].size(); j++)
        {
            if (nodes[i].get(j).getValue()==rhs)
                return nodes[i].get(j);
        }
    }
}

template <class K, class V>
LinkedList<HashNode<K, V>> HashTable<K,V>::getTable()
{
    return nodes;
}

template <class K, class V>
void HashTable<K,V>::clear()
{
    nodes.clear();
}

template <class K, class V>
HashTable<K,V>::~HashTable()
{
    clear();
}



#endif // HASHTABLE
