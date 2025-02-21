#include "../header/util.h"
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>


float Util::generateRandomWeight()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0, 1.0);

    float weight = dist(gen);
    return weight;
}


float Util::generateRandomBias()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-10, 10);

    float bias = dist(gen);
    return bias;
}


std::string Util::convertIntToString(int num)
{
    return std::to_string(num);
}


std::string Util::strLower(std::string str)
{
    std::string finalStr = "";
    for (char c : str)
        finalStr += std::tolower(c);
    return finalStr;
}


std::string Util::strUpper(std::string str)
{
    std::string finalStr = "";
    for (char c : str)
        finalStr += std::toupper(c);
    return finalStr;
}