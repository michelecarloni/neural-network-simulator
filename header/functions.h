#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

class Functions
{
    private:
        static const std::string arrActFunction[4];
        static std::vector<float> softmaxValuesVec;
    public:
        static void relu(float& num);
        static void sigmoid(float& num);
        static void tanh(float& num);
        static void softmax(float& num, std::vector<float>& vecValues, int index);
        static bool checkFunctionExist(std::string funName);
        static std::vector<float>& getSoftmaxValuesVec();
};

#endif