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
    char* analysis;
    Vector<int> functionSize;
    int varAmount;
    int varSize;
    Vector<String> files;
    HashTable<String, String> hash;
    AvlTree<String> tree;
    Stack<String>  functionStack;
    Vector<String> repeatedLines;
    Vector<int> zeroInstanceVars;
    Vector<int> threeInstanceVars;
    int conditionRepetition;
    int functionAmount;
    int mainlines;
    void variableParse(String);
    void conditionParse(String);
    void findRepetition(String, String);
    bool isControlStatement(String);
public:
    int codelines;
    Grader(char*);
    void getLines(std::ifstream&, String);
    void openDirectories(String);
    int averageFunctionSize();
    void metric1(std::fstream&);
    void metric2(std::fstream&);
    void metric3(std::fstream&);
    void metric4(std::fstream&);
    void metric5(std::fstream&);
    String getBaseName(String);
    void getscore(std::ofstream&, String);
};

#endif // GRADER

