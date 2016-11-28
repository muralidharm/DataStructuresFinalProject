#include "grader.h"
#include <iostream>
#include <fstream>
#include "DSString.h"
#include "stack.h"
Grader::Grader()
{
    score = 0;
}
void Grader::getLines(std::ifstream& input)
{
    String reader;
    String temp;
    while(input.peek() != EOF)
    {
        input >> reader;
        while (input.peek() != 10 && input.peek() != EOF)
        {
            reader = reader + " ";
            input >> temp;
            reader = reader + temp;
        }
        lines.add(reader);
    }
}

void Grader::metric1()
{
    float linecount = lines.size();
    float exceedschars = 0;
    for(int i = 0; i < linecount; i++)
    {
        if (lines[i].size() > 80)
        {
            exceedschars++;
            //std::cout << i << std::endl;
        }
    }
    score += (exceedschars/linecount)*20;
}
void Grader::metric2()
{
    Stack<int> commentStack;
    int linecount = lines.size();
    float commentScore = 0;
    for(int i = 0; i < linecount; i++)
    {
        if(lines[i][0] == '/')
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
    score += (int)commentScore;
}

int Grader::getscore()
{
    return score;
}
