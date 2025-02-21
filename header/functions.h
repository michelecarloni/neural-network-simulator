#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

class Functions
{
    private:
        static const std::string arrActFunction[3];
    public:
        static void relu(float& num);
        static void sigmoid(float& num);
        static void tanh(float& num);
        static bool checkFunctionExist(std::string funName);
};

#endif