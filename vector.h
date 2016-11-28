#ifndef VECTOR
#define VECTOR

#include<iostream>

template<class T>
class Vector{

  public:


      Vector(){ //Default constructor
      vectorSize = 0;
      cap = 10;
      list = new T[cap];
      }
      Vector(int newCap){ //Constructor that takes in integer as cap- used mostly in the resize function
      list = new T[newCap];
      vectorSize = 0;
      cap = newCap;
      }
      Vector(const Vector<T>& copyVector) //Creates a Vector based off of another Vector
      {
          cap = copyVector.cap;
          vectorSize = copyVector.size();
          list = new T[copyVector.cap];
          for (int i = 0; i < vectorSize; i++)
          {
              list[i] = copyVector.list[i];
          }

      }

      void add(T newObject) //Adds object to the end of the vector
      {
          if (vectorSize >= cap)
          {
              resize();
          }
          list[vectorSize] = newObject;
          vectorSize += 1;
      }
      void add(T newObject, int index) //Adds object at specified index
      {
         if (index >= cap)
          {
              resize();
          }
          vectorSize++;
          for (int i = vectorSize-1; i >= 0; i--)
          {
              list[i] = list[i-1];
          }
          list[index] = newObject;
          vectorSize += 1;
      }
      T get(int index) //Retrieves object from index number
      {
          if (index < cap)
          {
          return list[index];
          }
          else
          {
              throw "Out of range.";
          }
      }
      ~Vector() //Destructor
      {
          delete[] list;
      }
      int size() const //Returns the size of the vector
      {
          return vectorSize;
      }
      void sort() //Uses bubble sort algorithm to sort objects from least to greatest
      {
          T swap;
          for (int i = 0; i < vectorSize; i++)
          {
              for (int j = 0; j < vectorSize-1; j++)
              {
                  if (list[j] > list[j+1])
                  {
                      swap = list[j];
                      list[j] = list[j+1];
                      list[j+1] = swap;
                  }
              }
          }
      }
      inline void sort(bool (comparisonFunction)(T, T)) //A sort method that takes in a function, used to solve problem with sorting pointers
      {
          T swap;
          for (int i = 0; i < vectorSize; i++)
          {
              for (int j = 0; j < vectorSize-1; j++)
              {
                  if (comparisonFunction(list[j], list[j+1]))
                  {
                      swap = list[j];
                      list[j] = list[j+1];
                      list[j+1] = swap;
                  }
              }
          }
      }

      T& operator[](int index) //Retrieves object by index, SHOULD NOT BE USED FOR ASSIGNMENT
      {
          if (index < cap)
          {
          return list[index];
          }
          else
          {
              throw "Out of range.";
          }
      }
      Vector<T>& operator=(Vector<T>& object) //Assignment operator using vector
      {
          int newSize = object.size();
          vectorSize = object.size();
          cap = object.cap;
          delete[] list;
          list = new T[object.cap];
          for (int i = 0; i < newSize; i++)
          {
              list[i] = object.list[i];
          }
          return *this;
      }
      Vector<T>& operator+=(T addedObject) //Addition operator
      {
          if (vectorSize >= cap)
          {
              resize();
          }
          list[vectorSize] = addedObject;
          vectorSize += 1;
          return *this;
      }
      void remove(int index) //Remove object at specified index
      {
          for (int i = index; i < vectorSize-1; i++)
          {
              list[i] = list[i+1];
          }
          vectorSize--;
      }
      void removeEnd()
      {
          vectorSize--;
      }

      void eliminateDuplicates() //In a sorted vector, removes multiple instances of an object
      {
          sort();
          //int length = vectorSize;
          for (int i = 1; i < vectorSize; i++)
          {
             if (list[i] == list[i-1])
             {
                 remove(i);
                 i--;
                //length --;
             }
          }
      }
      bool contains(T object) //Returns true if the object in in the Vector, otherwise returns false
      {
          sort();
          int left = 0;
          int right = vectorSize-1;
          int mid;
          while (left <= right)
          {
              mid =(int)((left+right)/2);
              if (object == list[mid])
                  return true;
              else if (object > list[mid])
                  left = mid + 1;
              else
                  right = mid - 1;
          }
          return false;
      }
      bool linearContains(T object)
      {
          for (int i = 0; i < vectorSize; i++)
          {
              if (list[i] == object)
                   return true;
          }
          return false;
      }
      int smallestIndex()
      {
          int index = 0;
          for (int i = 1; i < vectorSize; i++)
          {
              if (list[i] < list[index])
              {
                  index = i;
              }
          }
          return index;
      }
      T& lastElement()
      {
          return list[vectorSize-1];
      }
  private:

      void resize() //Resizes array, called when vectorSize exceeds cap
      {

          float newcap = 1.5*(float)cap;
          cap = (int)newcap;
          T* newList = new T[cap];
          for (int i = 0; i < vectorSize; i++)
          {
              newList[i] = list[i];
          }
          delete [] list;
          list = newList;
      }

      T* list; //List of objects of type T
      int vectorSize; //Keeps track of how many objects are in the vector.  Is incremented in addition functions
      int cap; //Actual size of list, increases each time vectorSize exceeds it

};

#endif
