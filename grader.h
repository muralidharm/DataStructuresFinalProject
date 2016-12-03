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
    Vector<Vector<String>> files;
    HashTable<String, String> hash;
    AvlTree<String> tree;
    Stack<String>  functionStack;
    int conditionRepetition;
    int codelines;
    int mainlines;
    void variableParse(String);
    void conditionParse(String);
    void findRepetition(String);
    bool isControlStatement(String);
public:
    Grader();
    void getLines(std::ifstream&, String);
    void metric1();
    void metric2();
    void metric3();
    void metric4();
    int getscore();
};

#endif // GRADER

