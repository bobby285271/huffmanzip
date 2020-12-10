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
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include "node.h"
#include "string-convert.h"

class orgTree
{
private:
    std::string file_str;
    std::map<char, int64_t> char_cnt_table;
    std::vector<node> tree_node_set;
    std::map<char, std::string> huffman_code_to_char;
    void read_origin_file(
        const char *origin_file);
    void build_huffman_tree();
    void initial_huffman_code_to_char();

public:
    orgTree(
        const char *origin_file);
    void get_encode_result(
        const char *dest_file);
};