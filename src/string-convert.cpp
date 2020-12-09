/* string-convert.cpp
 *
 * Copyright 2020 Bobby Rong
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "string-convert.h"

std::string binToChar(std::string &s)
{
    std::string t;
    for (size_t i = 0; i < s.size(); i += 8)
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
