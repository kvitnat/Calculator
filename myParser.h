//
// Created by admin on 16.02.2020.
//

#ifndef UNTITLED_MYPARSER_H
#define UNTITLED_MYPARSER_H


#include <iostream>
#include <cstring>
//using namespace std;
class myParser
{

private:
    enum Types { NONE, DELIMITER, NUMBER };
    std::string s = "";
    std::string exp;
    unsigned int expIdx;
    std::string token;
    Types tokType;

public:
    std::string str_error = "";

    myParser() { }
    ~myParser() { }

    double ExpressionStart(std::string expstr);
    void ExpPlusMin(double & result);
    void ExpMultdiv(double & result);

    void ExpUnar(double & result);
    void Atom(double & result);
    void GetToken();
    bool IsDelim(char c);
};
#endif //UNTITLED_MYPARSER_H
