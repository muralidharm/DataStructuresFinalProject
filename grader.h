#ifndef GRADER
#define GRADER
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "vector.h"
#include "hashtable.h"
class Grader {
private:
    int score;
    Vector<Vector<String>> files;
    HashTable<String, String> hash;
    int codelines;
    int mainlines;
public:
    Grader();
    void getLines(std::ifstream&, String);
    void metric1();
    void metric2();
    void metric3();
    int getscore();
};

#endif // GRADER

