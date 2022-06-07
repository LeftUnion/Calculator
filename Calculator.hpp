#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <stack>
#include <vector>
#include <map>

enum class opTypes
{
    Prefix,
    Postfix,
    binary
};

const std::map<std::string, opTypes> allOp
{
    {"!",   opTypes::Postfix},
    {"@",   opTypes::Prefix },
    {"sin", opTypes::Prefix },
    {"cos", opTypes::Prefix },
    {"tg", opTypes::Prefix },
    {"^",   opTypes::binary },
    {"+",   opTypes::binary },
    {"-",   opTypes::binary },
    {"*",   opTypes::binary },
    {"/",   opTypes::binary }
};

class Calculator
{
public:
    std::vector<std::string> mathString;
    std::vector<std::string> lineString;
    std::stack<std::string> capacity;

    Calculator() = default;

    double calculate(std::string &&input);

private:
    int priority(char op);
    void opn(std::vector<std::string> &&input);
    void parser(std::string &&input);

    double divide(double a, double b);
    double plus(double a, double b);
    double minus(double a, double b);
    double multiply(double a, double b);
    double pow(double a, double b);
    double uMinus(double a);
    double exp(double a);
    double cos(double a);
    double sin(double a);
    double tg(double a);
    double ctg(double a);
};

#endif // CALCULATOR_HPP
