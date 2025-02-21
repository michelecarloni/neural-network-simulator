#ifndef UTILS_H
#define UTILS_H

#include <string>

class Util
{
    public:
        static float generateRandomWeight();
        static float generateRandomBias();
        static std::string convertIntToString(int num);
        static std::string strLower(std::string str);
        static std::string strUpper(std::string str);
};




#endif