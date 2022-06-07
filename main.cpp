#include "Calculator.hpp"

#include <iostream>

int main()
{
    Calculator device;
    std::string expression;

    while(true)
    {
        std::cout << std::endl << "Input your expression:" << std::endl;
        std::getline(std::cin, expression);
        std::cout << device.calculate(std::move(expression)) << std::endl;
    }

    return 0;
}
