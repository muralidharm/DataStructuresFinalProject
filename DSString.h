#ifndef STRING
#define STRING

#include <iostream>
#include <cstring>

class String{

    public:

        String();
        String(const char*);
        String(const String&);

        String& operator= (const char*);
        String& operator= (const String&);
        String operator+ (const String&);
        bool operator== (const char*);
        bool operator== (const String&);
        bool operator> (const String&) const;
        bool operator< (const String&) const;
        char& operator[] (const int);

        int size() const;
        String substring(int, int);
        char* c_str();
        String& makeLowerCase();
        bool isLowerString();
        bool containsChar(const char);
        bool containsString(const String);
        char firstChar();
        int spaceInstance();
        String secondWord();
        String removePunctuation();
        bool isCFile();
        void clear();
        friend std::ostream& operator<< (std::ostream&, const String&);
        friend std::istream& operator>> (std::istream&, String&);

        char* data;

        ~String();


};


#endif
