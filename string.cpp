

#include "DSString.h"
#include <iostream>
#include <cstring>

String::String() //Default constructor
{
    char* s = "";
    data = new char[1];
    strcpy(data, s);
}
String::String(const char* s) //Takes in char* and sets as string
{

    data = new char[strlen(s)+1];
    strcpy(data, s);
}
String::String(const String &s) //Takes in String and copies data members
{
   if (s.data != nullptr)
   {
   data = new char[strlen(s.data)+1];
   strcpy(data, s.data);
   }

}
String& String::operator= (const char* s) //Assignment operator for char*
{
    if (this->data != s)
    {
        if (data != nullptr)
        {
            clear();
        }

        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }
    return *this;

}
String& String::operator= (const String &s) //Assignment operator for String
{
    if (this != &s)
    {
        if (data != nullptr)
        {
        clear();
        }
    data = new char[strlen(s.data)+1];
    strcpy(data, s.data);
    }
    return *this;
}

String String::operator+ (const String &s) //Puts together two strings
{
    char addition[size()+s.size()+1];
    strcpy(addition, data);
    strcat(addition,s.data);
    addition[size()+s.size()] = '\0';
    String addedString = String(addition);
    return addedString;

}

bool String::operator==(const char* s) //Equality operator to char*
{
    int compare = strcmp(data, s);
    if (compare == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool String::operator==(const String &s) //Equality operator to String
{
    int compare = strcmp(data, s.data);
    if (compare == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool String::operator>(const String &s) const //Greater than operator
{
    int compare = strcmp(data, s.data);
    return (compare > 0);
}
bool String::operator<(const String &s) const //Greater than operator
{
    int compare = strcmp(data, s.data);
    return (compare < 0);
}
char& String::operator[](const int i) //Index for String
{
   if (i < 0)
   {
        return data[ i+ size()];
   }
   else
   {
        return data[i];
   }
}


void String::clear() //Clears out string and assigns it to null
{
    if (data != nullptr)
        delete[] data;
    data = nullptr;
}


String::~String() //Destructor for string
{
    if (data != nullptr)
    {
        clear();
    }
}
int String::size() const //Returns size of string
{
    if (this->data != nullptr)
    {
        return strlen(data);
    }
    else
    {
        return 0;
    }
}
String String::substring(int start, int end) //Returns substring from starting point to ending point
{
    if (start < 0)
    {
        start += size();
    }
    if (end < 0)
    {
        end += size();
    }
    char sub[end-start+1];
    for (int i = 0; i < end-start; i++)
    {
        sub[i] = data[start+i];
    }
    sub[end-start] = '\0';
    String newstring = String(sub);
    return newstring;
}

char* String::c_str() //Returns string data member
{

    char* newstring = new char[this->size()+1];
    if (this->data != nullptr)
    {
        strcpy(newstring, data);

    }
    else
    {
        newstring[0] = '\0';

    }
    return newstring;
    delete newstring;
}
String& String::makeLowerCase() //Makes entire string lowercase
{
   int length = (int)strlen(data);
   for (int i = 0; i < length; i++)
   {
       data[i] = tolower(data[i]);
   }
   return *this; //I understand that this implementation will alter the original string, but for sorting purposes I am doing this intentionally.
}
bool String::isLowerString() //Returns true if every character in the string is lowercase
{
    int length = (int)strlen(data);
    for (int i = 0; i < length; i++)
    {
        if (isupper(data[i]))
        {
            return false;
        }
    }
    return true;
}
bool String::containsChar(const char c) //Check if a String contains another String
{
    int length1 = (int)strlen(data);
    for (int i = 0; i < length1; i++)
    {
        if(data[i] == c)
            return true;
    }
    return false;
}
bool String::containsString(const String s)
{
    int start = 0;
    int end = s.size();
    while(end <= this->size())
    {
        String sub = substring(start, end);
        if (substring(start, end) == s)
            return true;
        else
        {
            start ++;
            end ++;
        }

    }
    return false;
}

char String::firstChar() //Returns the first character of a string- I'm using this for formatting the contents of the output file
{
    return data[0];
}
int String::spaceInstance()
{
    int space = 0;
    int length = (int)strlen(data);
    for (int i = 0; i < length; i++)
    {
        if(data[i] == 32)
            space++;
    }
    return space;
}
String String::secondWord()
{
    int length = strlen(data);
    int newsize = 0;
    for (int i = 0; i < length; i++)
    {
        newsize++;
        if (data[i] == 32)
            break;
    }
    String newstring;
    if (data[length-1] == ';')
        newstring = substring(newsize, length-1);
    else
        newstring = substring(newsize, length);
    return newstring;
}
//Removes punctuation from a string.  It's poorly written but mostly does its job.
String String::removePunctuation()
{
    int stringSize = strlen(data);
    int newStringSize = 0;
    int newCounter = 0;
    bool parenthesesCond = false;
    for (int i = 0; i < stringSize; i++)
    {
        if((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z'))
            newStringSize++;
        if(data[i] == '(' )
        {
            parenthesesCond = true;
            break;
        }
    }
    char* newData = new char[newStringSize+1];
    for (int i = 0; i < stringSize; i++)
    {
        if(((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')) && (i < newStringSize || !parenthesesCond))
        {
            newData[newCounter] = data[i];
            newCounter++;
        }

    }
    newData[newStringSize] = '\0';
    return String(newData);
    /* int length = strlen(data);
    int index = 0;
    char* newData = new char[length];
    for (int i = 0; i < length; i++)
    {
        if ((data[i] >= 'a' && data[i] <= 'z' ) || (data[i] >= 'A' && data[i] <= 'Z' ))
        {
            newData[index] = data[i];
            index++;
        }
    }
    data[index] = '\0';
    String s = *this;
    //delete newData;
    if (length > 1)
    {
    if(data[0] == '"' && data[length-1] == '"')
    {
        if (data[length-2] == '.' || data[length-2] == '!' || data[length-2] == '?' || data[length-2] == ',')
            s = s.substring(1, length-2);
        else
            s = s.substring(1, length-1);
    }
    else if (data[0] == '"')
    {
        s = s.substring(1, length);
    }
    else if (data[length-1] == '"')
    {
        if (data[length-2] == '.' || data[length-2] == '!' || data[length-2] == '?' || data[length-2] == ',')
            s = s.substring(0, length-2);
        else
            s = s.substring(0, length);
    }
    if(data[0] == '(' && data[length-1] == ')')
    {
        s = s.substring(1, length-1);
    }
    else if (data[0] == '(')
        s = s.substring(1, length);
    else if (data[length-1] == ')')
        s = s.substring(0, length-1);
    if(data[0] == '\'' && data[length-1] == '\'')
    {
        s = s.substring(1, length-1);
    }
    else if (data[0] == '\'')
        s = s.substring(1, length);
    else if (data[length-1] == '\'')
        s = s.substring(0, length-1);
    if (data[length-1] == '.' || data[length-1] == '!' || data[length-1] == '?' || data[length-1] == ',')
    {
        if (data[length-2] == ')' || data[length-2] == '"')
            s = s.substring(0, length-2);
        else
            s = s.substring(0, length-1);
    }
    }
    return s;*/
}
bool String::isCFile()
{
    int stringSize = strlen(data);
    String s = substring(stringSize-3, stringSize);
    if (substring(stringSize-4, stringSize) == ".hpp")
        return true;
    else if (substring(stringSize-4, stringSize) == ".cpp")
        return true;
    else if (substring(stringSize-2, stringSize) == ".c")
        return true;
    else if (substring(stringSize-2, stringSize) == ".h")
        return true;
     else if (substring(stringSize-3, stringSize) == ".cc")
        return true;
    else
        return false;
}
std::ostream& operator<<(std::ostream& os, const String& s) //Overloaded extraction operator
{
    os << s.data;
    return os;
}
std::istream& operator>>(std::istream& is, String& s) //Overloaded insertion operator- using to read in data from file
{
    char temp[80] = "";
        is >> temp;

        if (s.data) delete[] s.data;

        s.data= new char[strlen(temp) + 1];
        strcpy(s.data, temp);

        return is;
}
