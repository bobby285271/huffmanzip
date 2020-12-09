/* encode.h
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

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include "node.h"
#include "string-convert.h"

class orgTree
{
private:
    std::string str;
    std::map<char, int> arr;
    std::vector<node> T;
    std::map<char, std::string> Code;
    void readOriginFile(char *org);
    void buildTree();
    void Hfmcode();

public:
    orgTree(char *org);
    void getEncodeResult(char *file);
};