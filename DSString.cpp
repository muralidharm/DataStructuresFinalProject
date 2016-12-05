#include <iostream>
#include <cstring>
#include "DSString.h"
using namespace std;

String::String()
{
    const char* rhs = "";
    data = new char [strlen(rhs)+1];
    strcpy(data, rhs);
}

String::String(const String& rhs)
{
    data = new char [rhs.size() +1];
    strcpy(data, rhs.data);
}

String::String(const char* rhs)
{
    if (rhs!=nullptr)
    {
        data = new char [strlen(rhs) +1];
        strcpy(data, rhs);
    }
    else {
        data = new char [strlen("") + 1];
        strcpy(data, "");
    }
}

String::~String()
{
    if(data != nullptr)
        delete[] data;
}

String& String::operator= (const String& rhs)
{
    if (data!=nullptr)
        delete [] data;
    if (rhs.data != nullptr)
    {
        data=new char [rhs.size() +1];
        for (int i = 0; i < rhs.size(); i++)
        {
            data[ i ] = rhs.data[ i ];
        }
        data[rhs.size()] = '\0';
    }
    return *this;
}

String& String::operator= (const char* rhs)
{
    if (data!=nullptr)
        delete[ ] data;
    if (rhs != nullptr)
    {
        data=new char [strlen(rhs)+1];
        for (int i = 0; i < strlen(rhs); i++)
        {
            data[ i ] = rhs[ i ];
        }
        data[strlen(rhs)] = '\0';
    }
    return *this;
}

bool String::operator==(const String& rhs) const
{
    //cout << data << " " << rhs.data << endl;
    if (rhs.data != nullptr)
    {
        int solution=strcmp(data, rhs.data);
        if (solution==0)
            return true;
    }
    return false;
}

bool String::operator==(const char* rhs) const
{
    if (rhs != nullptr)
    {
        int solution=strcmp(data, rhs);
        if (solution==0)
            return true;
    }
    return false;
}

bool String::operator!=(const String& rhs) const
{
    if (rhs.data != nullptr)
    {
        int solution=strcmp(data, rhs.data);
        if (solution!=0)
            return true;
    }
    return false;
}

String String::operator+ (const String& rhs)
{
    int length=size() + rhs.size() + 1;
    char* temp = new char[length+1];
    for (int i = 0; i < size(); i++)
    {
        temp[ i ] = data[ i ];
    }
    for (int j = size(); j<length; j++)
    {
        temp[ j ] = rhs.data[ j - size()];
    }
    temp[length]=0;
    return temp;
}

bool String::operator> (const String& rhs) const
{
    if (rhs.data != nullptr)
    {
        int solution=strcmp(data, rhs.data);
        if (solution>0)
            return true;
    }
    return false;
}

bool String::operator< (const String& rhs) const
{
    if (rhs.data != nullptr)
    {
        int solution=strcmp(data, rhs.data);
        if (solution<0)
            return true;
    }
    return false;
}


bool String::operator<= (const String& rhs) const
{
    if (rhs.data != nullptr)
    {
     //   int solution=strcmp(data, rhs.data);
        if (!(operator>(rhs)))
            //		if (!*this > rhs)
            return true;
    }
    return false;
}

bool String::operator>= (const String& rhs) const
{
    if (rhs.data != nullptr)
    {
        //int solution=strcmp(data, rhs.data);
        if (operator>(rhs) or operator==(rhs))
            return true;
    }
    return false;
}

char& String::operator[] (const int index)
{
    int negSize=size() * -1;
    int posIndex=(negSize-index) * -1;
    if (index>=0 and index<size())
    {
        return data[index];
    }
    else
    {
        if (index<0 and posIndex<size())
        {
            return data[posIndex];
        }
    }
    return data[0];
}

int String::size() const
{
    int length=0;
    if (data != nullptr)
    {
        length = strlen(data); //error
    }
    return length;
}

String String::substring(int start)
{
    char* temp;
    int j=0;
    int finish=strlen(data);
    int length=finish-start;
    temp = new char[length+1];
    for (int i=start; i<finish; i++)
    {
        temp[ j ] = data[ i ];
        j++;
    }
    temp[length+1] = '\0';
    return temp;
}

String String::substring(int start, int finish)
{
    int length;
    char* temp;
    int posStart = start;
    int posFinish = finish;
    if (start<0)
    {
        posStart = start + size();
    }
    if (finish<0)
    {
        posFinish = finish + size();
    }
    length=finish-start;
    if (start>=0 and finish<0)
    {
        length=start-finish;
    }
    temp = new char[length+1];
    int j=0;
    for (int i=posStart; i<posFinish; i++)
    {
        temp[ j ] = data[ i ];
        j++;
    }
    temp[posFinish] = '\0';
    return temp;
}

void String::remPun()
{
    int numPunctChars = 0;
    for (int i = 0; i < strlen(data); i++)
        if(ispunct(data[i]))
            numPunctChars ++;

    int newStringLength = strlen(data) - numPunctChars;
    char* tempStr = new char[newStringLength + 1];

    int newStrCounter = 0;
    for(int i = 0; i < strlen(data); i++)
        if(!ispunct(data[i]))
        {
            tempStr[newStrCounter] = data[i];
            newStrCounter ++;
        }
    tempStr[newStringLength] = '\0';

    delete[] data;
    data = tempStr;

}

void String::makeLower()
{
    for (int i = 0; i < strlen(data); i++)
    {
        data[i] = tolower(data[i]);
    }
}

char* String::c_str()
{
    return data;
}

std::ostream& operator<< (std::ostream& out, const String& line)
{
    out << line.data;
    return out;
}

std::istream& operator>> (std::istream& in, String& line)
{
    char buffer[500];
    in >> buffer;
    if (line.data != nullptr)
        delete[] line.data;
    line.data = new char[strlen(buffer) +1];
    strcpy(line.data, buffer);
    return in;
}
