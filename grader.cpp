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
    newVector.add(name);
    while(input.peek() != EOF)
    {
        input >> reader;
        while (input.peek() != 10 && input.peek() != EOF)
        {
            input >> temp;
            if (temp.containsChar('=') && name == "main.cpp")
            {
                variableParse(reader);
            }
            reader = reader + " ";
            reader = reader + temp;
        }
        if (reader.spaceInstance() == 1 && !reader.containsChar('=') && reader.firstChar() != '#' && name == "main.cpp")
            variableParse(reader);
        conditionParse(reader);
        newVector.add(reader);
        if (name == "main.cpp")
            mainlines++;
        codelines++;
    }
    files.add(newVector);
}
void Grader::variableParse(String var)
{
    if(!(var.substring(0,2) == "if" || var.substring(0,3) == "for" || var.substring(0, 5) == "while" || var.substring(0,2) == "//" || var.substring(0,6) == "return"))
    {
        if (var.containsChar(32) && !var.containsChar('.'))
        {
            //std::cout << var.secondWord() << std::endl;
            tree.insert(var.secondWord());
        }
    }
}
void Grader::conditionParse(String cond)
{
    if(cond.substring(0,3) == "for")
        conditionHash.addNode("for", cond);
    if(cond.substring(0,2) == "if")
        conditionHash.addNode("if", cond);
    if(cond.substring(0,5) == "while")
        conditionHash.addNode("while", cond);
    if(cond.substring(0,4) == "else")
        conditionHash.addNode("else", cond);
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
    //float mainscore = 500*(float)hash.returnList("main.cpp").size()/(float)hash.countersize();
    float mainscore = 500*((float)mainlines/(float)codelines);
    if (mainscore <= 20)
        score += mainscore;
    else
        score += 20;
}

int Grader::getscore()
{
    return score;
}
