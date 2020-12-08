#include "stringConvert.h"

std::string binToChar(std::string &s)
{
    std::string t;
    for (int i = 0; i < s.size(); i += 8)
    {
        std::bitset<8> a(s.substr(i, 8));
        t += a.to_ulong();
    }
    return t;
}

std::string charToBin(std::string &s)
{
    std::string t;
    for (char &c : s)
    {
        std::bitset<8> a(c);
        t += a.to_string();
    }
    return t;
}
