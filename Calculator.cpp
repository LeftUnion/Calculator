#include "Calculator.hpp"

#include <ctype.h>
#include <cmath>
#include <iostream>
#include <algorithm>

double Calculator::calculate(std::string &&input)
{

    double answer;

    parser(std::move(input));
    opn(std::move(lineString));
    while(!mathString.empty())
    {
        if(mathString[0] == "")
            break;
        std::string symb = mathString[0];
        mathString.erase(mathString.begin());

        if(std::isdigit(symb[0]))
            capacity.push(symb);
        else
        {
            double a, b;
            b = std::stod(capacity.top());
            capacity.pop();

            switch (symb[0])
            {
            case '+':
                a = std::stod(capacity.top());
                capacity.pop();
                capacity.push(std::to_string(plus(a, b)));
                break;

            case '-':
                a = std::stod(capacity.top());
                capacity.pop();
                capacity.push(std::to_string(minus(a, b)));
                break;

            case '*':
                a = std::stod(capacity.top());
                capacity.pop();
                capacity.push(std::to_string(multiply(a, b)));
                break;

            case '/':
                if(iszero(b))
                {
                    std::cout << "You can't divide on 0" << std::endl;
                    exit(1);
                }
                a = std::stod(capacity.top());
                capacity.pop();
                capacity.push(std::to_string(divide(a, b)));
                break;

            case '@':
                capacity.push(std::to_string(uMinus(b)));
                break;

            case '^':
                a = std::stod(capacity.top());
                capacity.pop();
                capacity.push(std::to_string(Calculator::pow(a, b)));
                break;
            }
        }
    }

    answer = std::stod(capacity.top());
    capacity.pop();

    return answer;
}

int Calculator::priority(char op)
{
    switch (op)
    {
    case '+':
        return 1;
        break;

    case '-':
        return 1;
        break;

    case '*':
        return 2;
        break;

    case '/':
        return 2;
        break;

    case '^':
        return 3;

    case 'S':
        return 3;

    case 'C':
        return 3;

    case 'T':
        return 3;

    case '@':
        return 10;
        break;

    case '(':
        return -1;
        break;
    }
}

void Calculator::opn(std::vector<std::string> &&input)
{
    if(lineString[0] == "-")
        lineString[0] = "@";

    while(!lineString.empty())
    {
        std::string symb = lineString[0];
        lineString.erase(lineString.begin());
        if(symb == "(" && lineString[0] == "-")
        {
            lineString[0] = "@";
        }

        auto it = allOp.find(symb);
        if(std::isdigit(symb[0]) || ((it->second == opTypes::Postfix) && it != allOp.end()))
            mathString.push_back(symb);

        if(it->second == opTypes::Prefix && it != allOp.end())
            capacity.push(symb);

        if(symb == "(")
            capacity.push(symb);

        if(symb == ")")
        {
            while(capacity.top() != "(")
            {
                mathString.push_back(capacity.top());
                capacity.pop();
            }
            capacity.pop();
        }

        if(it->second == opTypes::binary && it != allOp.end())
        {
            while(!capacity.empty() && priority(capacity.top()[0]) >= priority(symb[0]))
            {
                mathString.push_back(capacity.top());
                capacity.pop();
            }
            capacity.push(symb);
        }
    }

    while(!capacity.empty())
    {
        mathString.push_back(capacity.top());
        capacity.pop();
    }
}

void Calculator::parser(std::string &&input)
{
    input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
    std::string num;
    while(!input.empty())
    {
        if(isdigit(input[0]) || input[0] == '.')
        {
            num.push_back(input[0]);
            input.erase(0, 1);
        }
        else
        {
            if(!num.empty())
            {
                lineString.push_back(num);
                num.clear();
            }
            lineString.push_back(std::string(1, input[0]));
            input.erase(0, 1);
        }
    }
    lineString.push_back(num);
    num.clear();

}

double Calculator::divide(double a, double b)
{
    return a/b;
}

double Calculator::plus(double a, double b)
{
    return a + b;
}

double Calculator::minus(double a, double b)
{
    return a - b;
}

double Calculator::multiply(double a, double b)
{
    return a * b;
}

double Calculator::uMinus(double a)
{
    return a * (-1);
}

double Calculator::exp(double a)
{
    return std::exp(a) ;
}

double Calculator::cos(double a)
{
    return std::cos(a);
}

double Calculator::sin(double a)
{
    return std::sin(a);
}

double Calculator::tg(double a)
{
    return std::tan(a);
}

//double Calculator::ctg(double a)
//{
//    return std::;
//}

double Calculator::pow(double a, double b)
{
    return std::pow(a, b);
}
