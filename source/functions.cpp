#include "../header/functions.h"
#include <iostream>
#include <cmath>
#include <string>
#include <vector>


const std::string Functions::arrActFunction[4] = {"relu", "sigmoid", "tanh", "softmax"};
std::vector<float> Functions::softmaxValuesVec = {};

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

void Functions::softmax(float& num, std::vector<float>& vecValues, int index)
{
    float numerator = vecValues[index];
    float expNumerator = exp(numerator);
    float denominator = 0;

    for (float val : vecValues)
    {
        denominator += exp(val);
    }

    num = expNumerator / denominator;
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

std::vector<float>& Functions::getSoftmaxValuesVec() {return softmaxValuesVec;}