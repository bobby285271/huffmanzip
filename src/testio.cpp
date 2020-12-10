/* testio.cpp
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

#include "testio.h"

bool file_ifstream_check(const char *file_to_test)
{
    if (file_to_test == nullptr || strlen(file_to_test) < 2 || file_to_test[0] != '/')
    {
        return false;
    }
    std::ifstream infile_stream(file_to_test,
                                std::ios::in | std::ios::binary);

    return infile_stream ? true : false;
}

bool file_ofstream_check(const char *file_to_test)
{
    if (file_to_test == nullptr || strlen(file_to_test) < 2 || file_to_test[0] != '/')
    {
        return false;
    }
    std::ofstream outfile_stream(file_to_test,
                                 std::ios::out | std::ios::binary);

    return outfile_stream ? true : false;
}