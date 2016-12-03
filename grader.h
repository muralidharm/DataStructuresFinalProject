#ifndef GRADER
#define GRADER
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "vector.h"
#include "hashtable.h"
#include "avltree.h"
class Grader {
private:
    int score;
    Vector<Vector<String>> files;
    HashTable<String, String> hash;
    HashTable<String, String> conditionHash;
    AvlTree<String> tree;
    int codelines;
    int mainlines;
    void variableParse(String);
    void conditionParse(String);
public:
    Grader();
    void getLines(std::ifstream&, String);
    void metric1();
    void metric2();
    void metric3();
    int getscore();
};

#endif // GRADER

