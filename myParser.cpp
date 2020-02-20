//
// Created by admin on 16.02.2020.
//

#include "myParser.h"

double myParser::ExpressionStart(std::string expstr)
{
    double result;
    exp = expstr;

    int l = exp.length();

    if (exp[l - 1] == '+' || exp[l - 1] == '-' || exp[l - 1] == '/' ||
        exp[l - 1] == '*' || exp[l - 1] == '%')
    {
        str_error = "Last lex should be expression";
    }
    expIdx = 0;
    try
    {
        GetToken();
        if (token == "")
        {
            str_error = "no expression";
            return 0;
        }
        ExpPlusMin(result);
        if (token != "")
        {
            std::cout << "last lex should be = 0";
        }
        return result;
    }
    catch (std::exception ex)
    {
        return 0;
    }
}


void myParser::ExpPlusMin(double & result)
{
    std::string op;
    double partialResult;

    ExpMultdiv(result);
    while ((op = token) == "+" || op == "-")
    {
        GetToken();
        ExpMultdiv(partialResult);

        if (op == "-")
            result -= partialResult;

        if (op == "+")
            result += partialResult;

    }
}


void myParser::ExpMultdiv(double & result)
{
    std::string op;
    double partialResult = 0;
    ExpUnar(result);
    while ((op = token) == "*" || op == "/" || op == "%")
    {
        GetToken();
        if (token == "")
        {
            str_error = "last lex should be expression\n";
            return;
        }
        ExpUnar(partialResult);

        if (op == "*")
            result *= partialResult;

        if (op == "/")
        {

            if (partialResult == 0)
                str_error = "Division by zero";
            else
                result /= partialResult;
        }

        if (op == "%")
        {
            if (partialResult == 0)
            {
                str_error = "Division by zero";
            }
            else
                result = (int)(result) % (int)(partialResult);
        }
    }
}


void myParser::ExpUnar(double & result)
{
    std::string op = "";
    if ((tokType == DELIMITER) && (token == "+" || token == "-"))
    {
        op = token;
        GetToken();
    }
    Atom(result);
    if (op == "-") result = -result;
}


void myParser::Atom(double & result)
{
    switch (tokType)
    {
        case NUMBER:
            try
            {
                result = stod(token);
            }
            catch (std::invalid_argument& e)
            {
                result = 0;
                str_error = "syntax error";
            }
            GetToken();
            return;
        default:
            result = 0;
            break;
    }
}


void myParser::GetToken()
{
    tokType = NONE;
    token = "";
    if (expIdx == exp.length()) return;

    while (expIdx < exp.length() && exp[expIdx] == ' ')
        ++expIdx;
    if (expIdx == exp.length()) return;

    if (IsDelim(exp[expIdx]))
    {
        token += exp[expIdx];
        expIdx++;
        tokType = DELIMITER;
    }
    else if (exp[expIdx] >= '0' && exp[expIdx] <= '9')
    {
        while (!IsDelim(exp[expIdx]))
        {
            token += exp[expIdx];
            expIdx++;
            if (expIdx >= exp.length())
                break;
        }
        tokType = NUMBER;
    }
}

bool myParser::IsDelim(char c)
{
    const char* delims = "+-/*%";
    for(unsigned int i = 0; i < strlen(delims); ++i)
        if (c == delims[i])
            return true;
    return false;
}
