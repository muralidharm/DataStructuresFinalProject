#include <iostream>
#include <fstream>
//#include "DSString.h"
//#include "avltree.h"
#include <dirent.h>
#include "grader.h"
using namespace std;

int main(int argc, char* const argv[] )
{
    DIR *dir;
    struct dirent *ent;
    char c;
    Grader grader;
    if ((dir = opendir ("/home/ds/workspace/AutoIndexer")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        c = ent->d_name[strlen(ent->d_name)-1];
        if( c == 'h' || c == 'p' )
        {
            ifstream pathstream(ent->d_name);
            if (!pathstream.is_open())
                cerr << "Couldn't open file." << endl;
            String name = ent->d_name;
            grader.getLines(pathstream, name);
            pathstream.close();
        }
      }
      //grader.metric1();
      //grader.metric2();
      grader.metric3();
      std::cout << 100-grader.getscore() << std::endl;
      closedir (dir);
    } else {
      perror ("");
      return EXIT_FAILURE;
    }

}
