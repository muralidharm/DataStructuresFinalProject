#include <iostream>
#include <fstream>
#include "DSString.h"
#include "avltree.h"
#include <dirent.h>
#include "grader.h"
using namespace std;

int main(int argc, char* const argv[] )
{
    DIR *dir;
    struct dirent *ent;
    char c;
    if ((dir = opendir ("/home/ds/workspace/MiniSearch")) != NULL) {
      while ((ent = readdir (dir)) != NULL) {
        c = ent->d_name[strlen(ent->d_name)-1];
        if( c == 'h' || c == 'p' )
        {
            Grader grader;
            //std::cout << ent->d_name << std::endl;
            ifstream pathstream(ent->d_name);
            if (!pathstream.is_open())
                cerr << "Couldn't open file." << endl;
            grader.getLines(pathstream);
            std::cout << ent->d_name << std::endl;
            grader.metric1();
            grader.metric2();
            std::cout << 100-grader.getscore() << std::endl;
            pathstream.close();
        }
      }
      closedir (dir);
    } else {
      perror ("");
      return EXIT_FAILURE;
    }

}
