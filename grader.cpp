#include "grader.h"
#include <iostream>
#include <fstream>
#include "stack.h"
#include <dirent.h>
Grader::Grader()
{
    mainlines = 0;
    codelines = 0;
    conditionRepetition = 0;
    functionAmount = 0;
    varAmount = 0;
    varSize = 0;
}
void Grader::openDirectories(String p)
    {
        DIR *dir;
        struct dirent *ent;
        char c;
        if ((dir = opendir (p.c_str())) != NULL) {
          while ((ent = readdir (dir)) != NULL) {
            c = ent->d_name[strlen(ent->d_name)-1];
            String tempString = p + "/" + String(ent->d_name);
            if(ent->d_type == DT_DIR && c != '.')
                openDirectories(tempString);
            if( tempString.isCFile())
            {
                std::cout << ent->d_name << std::endl;
                ifstream pathstream(tempString.c_str());
                if (!pathstream.is_open())
                    cerr << "Couldn't open file." << endl;
                String name = ent->d_name;
                getLines(pathstream, name);
                pathstream.close();
            }
          }
          closedir (dir);
        }
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
            if (temp.containsChar('='))
            {
                variableParse(reader);
            }
            reader = reader + " ";
            reader = reader + temp;
            //temp = temp.removePunctuation();
        }
        if (reader.spaceInstance() == 1 && !reader.containsChar('=') && reader.firstChar() != '#' && name.containsString("main"))
            variableParse(reader);
        //conditionParse(reader);
        tree.inTreeString(reader);
        hash.addNode(name, reader);
        findRepetition(reader);
        if (name.containsString("main"))
            mainlines++;
        codelines++;
    }
    files.add(name);
}
void Grader::variableParse(String var)
{
    if(!(var.substring(0,2) == "if" || var.substring(0,3) == "for" || var.substring(0, 5) == "while" || var.substring(0,2) == "//" || var.substring(0,6) == "return"))
    {
        if (var.containsChar(32) && !var.containsChar('.'))
        {
            //std::cout << var.secondWord() << std::endl;
            tree.insert(var.secondWord().removePunctuation());
            varAmount++;
            varSize += var.secondWord().removePunctuation().size();
        }
    }
}
/*void Grader::conditionParse(String cond)
{
    if(cond.substring(0,3) == "for")
        conditionHash.addNode("for", cond);
    if(cond.substring(0,2) == "if")
        conditionHash.addNode("if", cond);
    if(cond.substring(0,5) == "while")
        conditionHash.addNode("while", cond);
    if(cond.substring(0,7) == "else if")
        conditionHash.addNode("else if", cond);
}*/
void Grader::findRepetition(String s)
{
    String pop;
    Vector<String> stringVector;
    if (s.containsChar('{'))
    {
        functionStack.push(s);
        functionAmount++;
    }
    if (!functionStack.isEmpty())
        functionStack.push(s);
    if (s.containsChar('}'))
    {
        while(!functionStack.peek().containsChar('{'))
        {
           pop = functionStack.pop();
           if (stringVector.contains(pop) && isControlStatement(pop))
               conditionRepetition++;
           else
               stringVector.add(pop);
        }
        functionSize.add(stringVector.size());
        stringVector = Vector<String>();
    }

}
bool Grader::isControlStatement(String var)
{
   return( var.substring(0,2) == "if" || var.substring(0,3) == "for" || var.substring(0, 5) == "while" || var.substring(0,5) == "switch");
}
int Grader::averageFunctionSize()
{
    int average = 0;
    int size = functionSize.getLength();
    for (int i = 0; i < size; i++)
    {
        average += functionSize[i];
    }
    return average/size;
}

void Grader::metric1()
{
    float charscore;
    float filecount = files.getLength();
    for(int i = 0; i < filecount; i++)
    {
        String file = files[i];
        int linecount = hash.returnList(file).size();
        float exceedschars = 0;
        for (int j = 0; j < linecount; j++)
        {
            if (hash.returnList(file).get(j).getValue().size() > 80)
            {
                exceedschars++;
            }
        }
        charscore += ((exceedschars/linecount)+.25)*20;
    }
    if (charscore == 0)
        scores.add(0);
    else
        scores.add((charscore/filecount));
}
void Grader::metric2()
{
    Stack<int> commentStack;
    int filecount = files.getLength();
    scores.add(0);
    int tooMany = 0;
    int tooFew = 0;
    for(int i = 0; i < filecount; i++)
    {
        String file = files[i];
        int linecount = hash.returnList(file).size();
        for(int j = 0; j < linecount; j++)
        {
            if(hash.returnList(file).get(j).getValue().firstChar() == '/')
                commentStack.push(1);
            else
            {
                if(commentStack.isEmpty())
                    tooFew++;
                else if (!commentStack.isEmpty())
                    commentStack.pop();
            }
            if (commentStack.size() > 10)
                tooMany++;
        }

    }
    tooFew /= 15;
    if (tooFew == 0)
        scores.add(5);
    else if ((tooMany == 0) && tooFew >= 1)
        scores.add(20);
    else if ((tooFew+tooMany)*.1 > 20)
        scores.add(20);
    else
        scores.add((tooFew+tooMany)*.1);
}
void Grader::metric3()
{

    float mainscore = 500*(float)mainlines/(float)hash.countersize();
    mainscore /= averageFunctionSize();
    if (mainscore <= 20)
        scores.add(mainscore);
    else
        scores.add(20);
}
void Grader::metric4()
{
    if (conditionRepetition == 0)
        scores.add(0);
    else
    {
        int linesPerRep = codelines/conditionRepetition;
        int temp;
        if (linesPerRep < 1000)
            temp = ((1000-linesPerRep)/1000);
        else
            temp = 0;
        scores.add((conditionRepetition/averageFunctionSize())*10+(temp*10));
    }
}
void Grader::metric5()
{
    int averageVar = varSize/varAmount;
    int zeroInstances = tree.zeroInstance();
    int threeInstances = tree.threeInstance();
    int temp;
    int timesL3 = codelines/threeInstances;
    if (timesL3 < 2000)
    {
        temp = (2000-timesL3)/2000;
    }
    else
        temp = 0;
    int score = ((averageVar/3)*5) + (zeroInstances*3) + (temp*7.5);
    if (score < 20)
        scores.add(score);
    else
        scores.add(20);

}

int Grader::getscore()
{
    return scores[0];
}
