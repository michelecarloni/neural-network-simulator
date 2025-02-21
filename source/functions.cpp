#include "../header/functions.h"
#include <iostream>
#include <cmath>
#include <string>


const std::string Functions::arrActFunction[3] = {"relu", "sigmoid", "tanh"};

void Functions::relu(float& num)
{
    if (num < 0)
        num = 0;
}

void Functions::sigmoid(float& num)
{
    num = 1/(1 + exp(-num));
}

void Functions::tanh(float& num)
{
    num = std::tanh(num);
}

bool Functions::checkFunctionExist(std::string funName)
{
    for (const std::string func : Functions::arrActFunction)
    {
        if (func == funName)
            return true;
    }
    return false;
}