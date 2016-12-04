#ifndef GRADER
#define GRADER
#include <iostream>
#include <fstream>
#include "stack.h"
#include "DSString.h"
#include "vector.h"
#include "hashtable.h"
#include "avltree.h"
class Grader {
private:
    Vector<int> scores;
    Vector<int> functionSize;
    int varAmount;
    int varSize;
    Vector<String> files;
    HashTable<String, String> hash;
    AvlTree<String> tree;
    Stack<String>  functionStack;
    int conditionRepetition;
    int functionAmount;
    int codelines;
    int mainlines;
    void variableParse(String);
    void conditionParse(String);
    void findRepetition(String);
    bool isControlStatement(String);
public:
    Grader();
    void getLines(std::ifstream&, String);
    void openDirectories(String);
    int averageFunctionSize();
    void metric1();
    void metric2();
    void metric3();
    void metric4();
    void metric5();
    int getscore();
};

#endif // GRADER

