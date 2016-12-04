#include <iostream>
#include <fstream>
//#include "DSString.h"
//#include "avltree.h"
#include <dirent.h>
#include "grader.h"
using namespace std;
int main(int argc, char* const argv[] )
{
    Grader grader;
    String path(argv[1]);
    grader.openDirectories(path);
    grader.metric1();
    grader.metric2();
    grader.metric3();
    grader.metric4();
    grader.metric5();
    //path.isCFile();

}
