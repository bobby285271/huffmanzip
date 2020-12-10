/* decode.h
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

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include "node.h"
#include "string-convert.h"

class destTree
{
private:
    std::vector<node> tree_node_set;
    std::string encoded_file_str;
    int64_t encoded_file_str_size;
    void read_compressed_file(
        const char *origin_file);

public:
    destTree(
        const char *origin_file);
    void get_decode_result(
        const char *dest_file);
};
