#ifndef GRADER
#define GRADER
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "vector.h"
class Grader {
private:
    int score;
    Vector<String> lines;
public:
    Grader();
    void getLines(std::ifstream&);
    void metric1();
    void metric2();
    int getscore();
};

#endif // GRADER

