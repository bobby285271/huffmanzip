/* decode.cpp
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

#include "decode.h"

destTree::destTree(const char *origin_file)
{
    read_compressed_file(origin_file);
}

void destTree::read_compressed_file(
    const char *origin_file)
{
    if (!strlen(origin_file) || origin_file[0] != '/')
    {
        throw "failed check: origin_file";
    }
    std::ios::sync_with_stdio(false);
    std::ifstream infile_stream(
        origin_file,
        std::ios::in | std::ios::binary);
    if (!infile_stream)
    {
        throw "failed check: infile_stream";
    }

    // Change the read position to the end to get the file size.
    infile_stream.seekg(0, std::ios::end);
    std::streampos file_len = infile_stream.tellg();
    if (!file_len)
    {
        throw "failed check: file_len";
    }

    infile_stream.seekg(0, std::ios::beg);

    int64_t tree_node_set_size;
    infile_stream.read((char *)&tree_node_set_size, sizeof(int64_t));
    tree_node_set.resize(tree_node_set_size);

    // Get the huffman tree built when compressing.
    infile_stream.read((char *)&tree_node_set[0], tree_node_set.size() * sizeof(node));
    infile_stream.read((char *)&encoded_file_str_size, sizeof(int64_t));

    encoded_file_str.assign(std::istreambuf_iterator<char>(infile_stream),
                            std::istreambuf_iterator<char>());

    // Convert each `char` into a 8-length binary string.
    encoded_file_str = charToBin(encoded_file_str);
    infile_stream.close();
}

void destTree::get_decode_result(
    const char *dest_file)
{
    std::ofstream outfile_stream(
        dest_file,
        std::ios::out | std::ios::binary);
    if (!outfile_stream)
    {
        throw "failed check: outfile_stream";
    }

    int64_t get_child_node_helper = tree_node_set.size() - 1;
    int64_t leaf_node_index = get_child_node_helper;

    // Look up for the character in the tree according to the huffman code.
    for (size_t i = 0; i < encoded_file_str_size; i++)
    {
        leaf_node_index =
            (encoded_file_str[i] == '0')
                ? tree_node_set[get_child_node_helper].child_node_id[0]
                : tree_node_set[get_child_node_helper].child_node_id[1];
        if (tree_node_set[leaf_node_index].child_node_id[0] == -1 &&
            tree_node_set[leaf_node_index].child_node_id[1] == -1)
        {
            outfile_stream.put(tree_node_set[leaf_node_index].char_name);
            get_child_node_helper = tree_node_set.size() - 1;
        }
        else
            get_child_node_helper = leaf_node_index;
    }
    outfile_stream.close();
}
