#include "cmake-build-debug/myParser.h"

double prevResults[10];
int count = 0;
std::string ReplaceLinks(std::string exp);

int main()
{
    std::string expression, expressionL;
    myParser parser;
    std::cout << "Calculator\n";
    std::cout << "Enter exit for exit\n";
    do
    {
        std::cout << "\nEnter your expression: ";
        getline(std::cin, expressionL);
        if(expressionL == "exit")
            break;

        expression = ReplaceLinks(expressionL);
        double result = parser.ExpressionStart(expression);

        if (parser.str_error == "")
        {
            for(int i = 9; i > 0; i--)
                prevResults[i] = prevResults[i-1];
            prevResults[0] = result;

            std::cout << "Result = " << result << "\n";
            count++;
        }
        else
        {
            std::cout << parser.str_error << "\n";
            parser.str_error = "";
        }
    }
    while(expression != "exit");
    return 0;
}

std::string ReplaceLinks(std::string exp)
{
    for(unsigned int i = 0; i < exp.length(); ++i)
    {
        if(exp[i] == '$')
        {
            int linkNum = exp[i+1] - '0';
            if (linkNum >= count)
                return "error";
            else
            {
                exp[i] = ' ';
                exp[i+1] = ' ';
                exp.insert(i, std::to_string(prevResults[linkNum]));
                return exp;
            }
        }
    }

    return exp;
}