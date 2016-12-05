#ifndef STRING
#define STRING

#include<iostream>

class String{

public:
    String();
    String(const char*);
    String(const String&);

    String& operator= (const char*);
    String& operator= (const String&);
    String operator+ (const String&);
    bool operator== (const char*) const;
    bool operator== (const String&) const;
    bool operator!=(const String& rhs) const;
    bool operator> (const String&) const;
    bool operator< (const String&) const;
    bool operator>= (const String&) const;
    bool operator<= (const String&) const;
    char& operator[] (const int);

    int size() const;
    String substring(int, int);
    String substring(int);
    void makeLower();
    void remPun();
    char * c_str();

    friend std::ostream& operator<< (std::ostream&, const String&);
    friend std::istream& operator>> (std::istream&, String&);

    ~String();

    char* data;

};

#endif
