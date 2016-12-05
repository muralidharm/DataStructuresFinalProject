#include "grader.h"
#include <iostream>
#include <fstream>
#include "stack.h"
#include <dirent.h>
Grader::Grader(char* a)
{
    analysis = a;
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
    AvlTree<String> tree;
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
            if (temp.containsChar('=') && !temp.containsChar('!') && !temp.containsChar('>') && !temp.containsChar('<') && !temp.containsString("=="))
            {
                variableParse(reader);
            }
            reader = reader + " ";
            reader = reader + temp;
            //temp = temp.removePunctuation();
        }
        if (reader.spaceInstance() == 1 && !reader.containsChar('#') && !reader.containsChar('=') && reader.firstChar() != '#' && name.containsString("main"))
            variableParse(reader);
        //conditionParse(reader);
        tree.inTreeString(reader);
        hash.addNode(name, reader);
        findRepetition(reader, name);
        if (name.containsString("main"))
            mainlines++;
        codelines++;
    }
    zeroInstanceVars.add(tree.zeroInstance());
    threeInstanceVars.add(tree.threeInstance());
    files.add(name);
}
void Grader::variableParse(String var)
{
    if(!(var.substring(0,2) == "if" || var.substring(0,3) == "for" || var.substring(0, 5) == "while" || var.substring(0,2) == "//" || var.substring(0,6) == "return" || var.containsChar('#')|| var.containsString(">>") || var.containsString("<<") || var.containsString("::")))
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
void Grader::findRepetition(String s, String name)
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
           {
               repeatedLines.add(pop + " in the file " + name);
               conditionRepetition++;
           }
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

void Grader::metric1(std::fstream& output)
{
    float charscore;
    int totalexceedschars;
    Vector<int> fileScores;
    Vector<int> fileExceeds;
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
        if (exceedschars == 0)
        {
            charscore += ((exceedschars/linecount))*20;
            fileScores.add(((exceedschars/linecount))*20);
        }
        else
        {
            charscore += ((exceedschars/linecount)+.25)*20;
            fileScores.add(((exceedschars/linecount)+.25)*20);
        }

        totalexceedschars += exceedschars;
        fileExceeds.add(exceedschars);
    }
    scores.add((charscore/filecount));
    output << "________________________________________________________________" << std::endl;
    output << '\n';
    output <<"Metric I Score: " << scores[0] << "/20." << std::endl;
    if (analysis[1] == 'v')
    {
        output << " Good coding standards propose that no lines be longer than eighty characters." <<  std::endl;
        output << " This code base contained " << totalexceedschars << " lines over eighty characters out of its total " << hash.countersize() << " lines." << std::endl;
        output << " The score represents the ratio of the lines over eighty characters to the total number " << std::endl;
        output << " of lines in the file and multiplying this fraction by the total possible 20 points." << std::endl;
        output << " Below a detailed report of the number of lines over eighty characters in each file is displayed. " << std::endl;
        for (int i = 0; i < files.getLength(); i++)
        {
            output << "     File " << files[i] << " received a " << fileScores[i] << "/20.The file contained "<< fileExceeds[i] << " lines over eighty characters out of its total " << hash.returnList(files[i]).size() << " lines." << std::endl;
        }
    }

}
void Grader::metric2(std::fstream& output)
{
    Stack<int> commentStack;
    int filecount = files.getLength();
    Vector<int> fileScores;
    Vector<int> fileComments;
    Vector<String> appropriateness;
    //scores.add(0);
    int totalCommented = 0;
    int totalUncommented = 0;
    int totalMany = 0;
    int totalFew = 0;
    for(int i = 0; i < filecount; i++)
    {
        String file = files[i];
        int tooMany = 0;
        int tooFew = 0;
        int commented = 0;
        int uncommented = 0;
        int linecount = hash.returnList(file).size();
        for(int j = 0; j < linecount; j++)
        {
            if(hash.returnList(file).get(j).getValue().firstChar() == '/')
            {
                commented++;
                commentStack.push(1);
            }
            else
            {
                uncommented++;
                if(commentStack.isEmpty())
                    tooFew++;
                else if (!commentStack.isEmpty())
                    commentStack.pop();
            }
            if (commentStack.size() > 10)
                tooMany++;
        }
        tooFew /= 15;
        if (tooFew == 0 && tooMany == 0)
            fileScores.add(0);
        else if (commented > uncommented)
            fileScores.add(5);
        else if (commented == 0 && (tooFew > tooMany))
            fileScores.add(20);
        else if ((uncommented/=15)/commented > 20)
            fileScores.add(20);
        else
            fileScores.add((uncommented/=15)/commented);
        totalFew += tooFew;
        totalMany += tooMany;
        totalCommented += commented;
        fileComments.add(commented);
        totalUncommented += uncommented;
        if ((tooFew > tooMany) && fileScores[i] >= 7)
            appropriateness.add(" too few");
        else if ((tooFew < tooMany) && fileScores[i] >= 7)
            appropriateness.add(" too many");
        else
            appropriateness.add(" appropriate");

    }
    int commentScore = 0;
    for(int i = 0; i < fileScores.getLength(); i++)
    {
        commentScore += fileScores[i];
    }
    scores.add(commentScore/fileScores.getLength());
    output << "________________________________________________________________" << std::endl;
    output << '\n';
    output << "Metric II Score: "<< scores[1] << "/20"<< std::endl;
    if (analysis[1] == 'v')
    {
        if (scores[1] < 6)
            output << "Well";
        else if (scores[1] < 12)
            output << "Moderately well";
        else
            output << "Poorly";
        output << " commented with";
        if ((totalFew > totalMany) && scores[1] >= 7)
            output << " too few";
        else if ((totalFew < totalMany) && scores[1] >= 7)
            output << " too many";
        else
            output << " appropriate";
         output << " comments." << std::endl;
         output << "The project contained " << totalCommented << " lines of commented code and "<< totalUncommented << " lines of uncommented code." << std::endl;
         output << "Below a detailed report of the scores for each file is displayed." << std::endl;
         for (int i = 0; i < filecount; i++)
         {

         output << "    File "<< files[i] << " received a " << fileScores[i] << "/20." << std::endl;

         output << "        The source code is ";
         if (fileScores[i] < 6)
             output << "well";
         else if (fileScores[i] < 12)
             output << "Moderately well";
         else
             output << "poorly";
         output << " commented with";
         output << appropriateness[i];
          output << " comments." << std::endl;

         output << "        The file contained "<< fileComments[i] <<" lines of commented code and " << (hash.returnList(files[i]).size()-fileComments[i]) << " lines of uncommented code." << std::endl;
         }
    }
}
void Grader::metric3(std::fstream& output)
{

    float mainscore = (float)mainlines;
    mainscore /= averageFunctionSize();
    if (mainlines == 0)
        scores.add(0);
    else if (mainscore <= 1)
        scores.add(0);
    else
    {

        if ((1-mainscore)*20 <= 20)
            scores.add(mainscore);
        else
            scores.add(20);
    }
    output << "________________________________________________________________" << std::endl;
    output << '\n';
    output << "Metric III Score: "<< scores[2] << "/20" << std::endl;
    if (analysis[1] == 'v')
    {
    output << " " << mainlines << " lines in main" << std::endl;

    output << " " << hash.countersize()-mainlines << " lines in rest of project" << std::endl;

    output << " " << functionAmount << " functions in project" << std::endl;

    output << " In good coding practice, the main.cpp file should be a relatively concise file which " << std::endl;
    output << " utilizes additional classes to perform most of the logic of the program." <<std::endl;
    if (mainscore <= 1)
    {
        output << " A good length of main.cpp relative to the average function size as main is " << std::endl;
        output << " shorter than the average function in the code base." << std::endl;
    }
    else if (mainscore <= 1.2)
    {
        output << " A relatively good length of main.cpp compared to the average function size, as main " << std::endl;
        output << " is less than 20 percent different than the average function size. However, main should " <<std::endl;
        output << " be shortened in order to be closer to (or ideally less than) the length of the average " << std::endl;
        output << " function size of the code base." << std::endl;
    }
    else if (mainscore <= 1.5)
    {
        output << " A relatively poor length compared to the average function size, as main is over a fourth " << std::endl;
        output << " longer than the length as the average function. However, main should be shortened in order " << std::endl;
        output << " to be closer to (or ideally less than) the length of the average function size of the code base." << std::endl;

    }
    else
    {
        output << " A poor length relative to the average function size, as main is over 50 percent longer than the " << std::endl;
        output << " average function. Thus, main should be shortened drastically to ensure that it is closer in length " << std::endl;
        output << " to the average function size of the code base." << std::endl;

    }
    }
}
void Grader::metric4(std::fstream& output)
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
    output << "________________________________________________________________" << std::endl;
    output << '\n';
    output << "Metric IV Score: "<< scores[3] <<"/20 " << std::endl;
    if (analysis[1] == 'v')
    {
        output << " In good coding practice, specific control statements such as for " << std::endl;
        output << " loop and while loops are not repeated multiple times in the same block of code." << std::endl;
        output << " This code base exhibited "<< conditionRepetition << " instances of control statement repetition within code blocks." << std::endl;
        if (conditionRepetition != 0)
        {
            output << "The following lines of code were repeated within the same function block:" << std::endl;
            for (int i = 0; i < repeatedLines.getLength(); i++)
            {
                output <<  repeatedLines[i] << std::endl;
            }
        }
    }
}
void Grader::metric5(std::fstream& output)
{
    Vector<int> fileScores;
    int averageVar = varSize/varAmount;
    for (int i = 0; i < files.getLength(); i++)
    {
    int zeroInstances = zeroInstanceVars[i];
    int threeInstances = threeInstanceVars[i];
    int temp;
    int timesL3;
    if (threeInstances != 0)
        timesL3 = varAmount/threeInstances;
    else
        timesL3 = 0;
    if (timesL3 < 2000)
    {
        temp = (2000-timesL3)/2000;
    }
    else
        temp = 0;
    int score = ((averageVar/30)*5) + (zeroInstances*3) + (temp*7.5);
    if (score < 20)
        fileScores.add(score);
    else
        fileScores.add(20);
    }
    int varScore = 0;
    for (int i = 0; i < fileScores.getLength(); i++)
    {
        varScore += fileScores[i];
    }
    varScore /= fileScores.getLength();
    scores.add(varScore);
    int totalZeros = 0;
    int totalThrees = 0;
    for (int i = 0; i < files.getLength(); i++)
    {
        totalZeros += zeroInstanceVars[i];
        totalThrees += threeInstanceVars[i];
    }
    totalZeros /= files.getLength();
    totalThrees /= files.getLength();
    output << "________________________________________________________________" << std::endl;
    output << '\n';
    output << "Metric V Score: " << scores[4] << "/20" << std::endl;
    if (analysis[1] == 'v')
    {

    output << " " << varAmount << " variables were declared." << std::endl;
    output << " In good coding practice, declared variables are used at least " << std::endl;
    output << " once and preferably several times in the project. " << std::endl;
    output << " There were " << totalZeros << " variables declared and not utilized in the code base, " << std::endl;
    output << " and " << totalThrees << " variables declared and utilized fewer than three times in the code base. " << std::endl;
    output << " In addition, the average variable length name was " << averageVar << ", which is a ___ average length." << std::endl;
    output << "Below a detailed report of the scores for each file is displayed." << std::endl;
    for(int i = 0; i < files.getLength(); i++)
        {
            output << "     File " << files[i] << " received a "<< fileScores[i] << "/20." << std::endl;

            output << "     " << zeroInstanceVars[i] << " variables that were declared and not utilized in the code base." << std::endl;
            output << "     " << threeInstanceVars[i] << " variables that were declared and utilized fewer than three times in the code base." << std::endl;
        }
    }

}
String Grader::getBaseName(String path)
{
    int decrement = path.size();
    for (int i = path.size()-1; i >= 0; i--)
    {
        if (path.c_str()[i] == '/')
            break;
        else
            decrement--;
    }
    return path.substring(decrement, path.size());
}

void Grader::getscore(std::ofstream& output, String path)
{
    int totalScore = 0;
    for (int i = 0; i < 5 ; i++)
    {
        totalScore += scores[i];
    }
    output << getBaseName(path) << std::endl;
    output << "Overall Score: " << totalScore << "/100, ";
    if (100-totalScore >= 90)
    {
        output << "A" <<std::endl;
        if (analysis[1] == 'v')
        {
            output << " This code base was incredibly well designed and performed appropriately on each of the five main metrics." << std::endl;
            output << " Great job! Please read below for a detailed analysis of the results of each metric." << std::endl;
        }
    }
    else if (100-totalScore >= 80)
    {
        output << "B" <<std::endl;
        if (analysis[1] == 'v')
        {
            output << "This code base was well designed and performed satisfactory on each of the five main metrics, "<< std::endl;
            output << "but source code quality could be improved.  Please read below for a detailed analysis of the " << std::endl;
            output << "results of each metric in order to better determine what upgrades are necessary to increase " <<std::endl;
            output << "the code base’s performance in the grader."  << std::endl;
        }
    }
    else if (100-totalScore >= 70)
    {
        output << "C" <<std::endl;
        if(analysis[1] == 'v')
        {
            output << "This code base was well designed and performed satisfactory o    n each of the five main metrics, "<< std::endl;
            output << "but source code quality could be improved.  Please read below for a detailed analysis of the " << std::endl;
            output << "results of each metric in order to better determine what upgrades are necessary to increase " <<std::endl;
            output << "the code base’s performance in the grader."  << std::endl;
        }
    }
    else if (100-totalScore >= 50)
    {
        output << "D" <<std::endl;
        if (analysis[1] == 'v')
        {
            output << "This code base was fairly well designed, though there are significant areas in which the source " << std::endl;
            output << "code quality could be improved. Please read below for a detailed analysis of the results of "<< std::endl;
            output << "each metric in order to better determine what upgrades are necessary to increase the code base’s " << std::endl;
            output << "performance in the grader" << std::endl;
        }
    }
    else if (100-totalScore >= 30)
    {
        output << "F" <<std::endl;
        if (analysis[1] == 'v')
        {
            output << "This code base was not well designed, and there are significant areas in " << std::endl;
            output << "which the source code quality must be improved. Please read below for a " << std::endl;
            output << "detailed analysis of the results of each metric in order to better determine " << std::endl;
            output << "what upgrades are necessary to increase the code base’s performance in the grader." << std::endl;
        }
    }
    else
    {
        output << "F" <<std::endl;
        if (analysis[1] == 'v')
        {
            output << "This code base was poorly designed, and there are significant areas in " << std::endl;
            output << "which the source code quality must be improved. Please read below for a " << std::endl;
            output << "detailed analysis of the results of each metric in order to better determine " << std::endl;
            output << "what upgrades are necessary to increase the code base’s performance in the grader." << std::endl;
        }
    }
    if (analysis[1] == 'v')
    {
        output << "Number of Files: " << files.getLength() << std::endl;
        output << "Average File Length: " << (hash.countersize()/files.getLength()) << std::endl;
    }

}
