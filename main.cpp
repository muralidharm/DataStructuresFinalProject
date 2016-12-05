#include <iostream>
#include <fstream>
//#include "DSString.h"
//#include "avltree.h"
#include <dirent.h>
#include "grader.h"
using namespace std;
int main(int argc, char* const argv[] )
{
    Grader grader(argv[2]);
    String path(argv[1]);
    std::fstream output1("help.txt", fstream::in | fstream::out);
    //output1.open("help.txt");
    std::ofstream output;
    output.open(argv[3]);
    grader.openDirectories(path);
    output << "STATIC CODE ANALYZER" << std::endl;
    if (grader.codelines == 0)
    {
        throw "File not found.";
    }
    grader.metric1(output1);
    grader.metric2(output1);
    grader.metric3(output1);
    grader.metric4(output1);
    grader.metric5(output1);
    grader.getscore(output, path);
    char output1Data[300];
    output1.clear();
    output1.seekg(0, ios::beg);
    while (output1.peek() != EOF)
    {
        output1.getline(output1Data, 300);
        output << output1Data<< std::endl;
    }

}
