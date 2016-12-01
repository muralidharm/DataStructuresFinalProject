#include "grader.h"
#include <iostream>
#include <fstream>
#include "stack.h"
Grader::Grader()
{
    score = 0;
    mainlines = 0;
    codelines = 0;
}
void Grader::getLines(std::ifstream& input, String name)
{
    String reader;
    String temp;
    Vector<String> newVector;
    while(input.peek() != EOF)
    {
        input >> reader;
        while (input.peek() != 10 && input.peek() != EOF)
        {
            reader = reader + " ";
            input >> temp;
            reader = reader + temp;
        }
        newVector.add(reader);
        hash.addNode(name, reader);
        if(name == "main.cpp")
            mainlines++;
        else
            codelines++;
    }
    files.add(newVector);
}

void Grader::metric1()
{
    float charscore;
    float filecount = files.size();
    for(int i = 0; i < filecount; i++)
    {
        int linecount = files[i].size();
        float exceedschars = 0;
        for (int j = 0; j < linecount; j++)
        {
            if (files[i][j].size() > 80)
            {
                exceedschars++;
            }
        }
        charscore += (exceedschars/linecount)*20;
    }
    score += (charscore/filecount);
}
void Grader::metric2()
{
    Stack<int> commentStack;
    int filecount = files.size();
    float commentScore = 0;
    for(int i = 0; i < filecount; i++)
    {
        int linecount = files[i].size();
        for(int j = 0; j < linecount; j++)
        {
            if(files[i][j][0] == '/')
                commentStack.push(1);
            else
            {
                if(commentStack.isEmpty() && commentScore < 20)
                    commentScore += .1;
                else if (!commentStack.isEmpty())
                    commentStack.pop();
            }
            if (commentStack.size() > 10 && commentScore < 20)
                commentScore += .05;
        }
        score += ((int)commentScore)/filecount;
    }
}
void Grader::metric3()
{
    //int hashmain = hash.returnList("main.cpp").size();
    float mainscore = 500*(float)hash.returnList("main.cpp").size()/(float)hash.countersize();
    if (mainscore <= 20)
        score += mainscore;
    else
        score += 20;
}

int Grader::getscore()
{
    return score;
}
