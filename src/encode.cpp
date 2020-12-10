/* encode.cpp
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

#include "encode.h"

orgTree::orgTree(
    const char *origin_file)
{
    read_origin_file(origin_file);
    build_huffman_tree();
    initial_huffman_code_to_char();
}

void orgTree::read_origin_file(
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

    file_str.reserve(file_len);
    file_str.assign(std::istreambuf_iterator<char>(infile_stream),
                    std::istreambuf_iterator<char>());

    infile_stream.close();
}

void orgTree::build_huffman_tree()
{
    // Calculate the frequency of each character.
    for (char &i : file_str)
    {
        char_cnt_table[i]++;
    }
    std::priority_queue<node> unmerged_node_queue;
    int64_t file_len = char_cnt_table.size();

    // Initial a tree for each character appeared.
    for (std::pair<const char, int64_t> &i : char_cnt_table)
    {
        node tree_node = {
            i.first,                       // tree_node.char_name
            (int64_t)tree_node_set.size(), // tree_node.id
            i.second,                      // tree_node.cnt_value
            -1,                            // tree_node.parent_node_id
            {-1,                           // tree_node.child_node_id[0]
             -1}};                         // tree_node.child_node_id[1]
        tree_node_set.push_back(tree_node);
        unmerged_node_queue.push(tree_node);
    }

    // Choose two trees which has the least cnt_value on its root,
    // perform merge operation.
    for (size_t i = 0; i < file_len - 1; i++)
    {
        node smallest_node_one = unmerged_node_queue.top();
        unmerged_node_queue.pop();
        node smallest_node_two = unmerged_node_queue.top();
        unmerged_node_queue.pop();
        node tree_node = {
            -1,                                                        // tree_node.char_name
            (int64_t)tree_node_set.size(),                             // tree_node.id
            smallest_node_one.cnt_value + smallest_node_two.cnt_value, // tree_node.cnt_value
            -1,                                                        // tree_node.parent_node_id
            {smallest_node_one.id,                                     // tree_node.child_node_id[0]
             smallest_node_two.id}};                                   // tree_node.child_node_id[1]
        tree_node_set.push_back(tree_node);
        unmerged_node_queue.push(tree_node);
        tree_node_set[smallest_node_one.id].parent_node_id =
            tree_node_set[smallest_node_two.id].parent_node_id =
                tree_node_set.size() - 1;
    }
}

void orgTree::initial_huffman_code_to_char()
{
    // For each character, initial its huffman code (a binary string)
    // according to the huffman tree built in orgTree::build_huffman_tree().
    for (node &i : tree_node_set)
    {
        std::string huffman_code;
        if (i.child_node_id[0] == -1 && i.child_node_id[1] == -1)
        {
            node get_parent_node_helper = i;
            while (get_parent_node_helper.parent_node_id >= 0)
            {
                node origin_node = get_parent_node_helper;
                get_parent_node_helper =
                    tree_node_set[get_parent_node_helper.parent_node_id];
                huffman_code.push_back(
                    '1' - (get_parent_node_helper.child_node_id[0] == origin_node.id));
            }
        }
        else
        {
            break;
        }
        std::reverse(huffman_code.begin(), huffman_code.end());
        huffman_code_to_char[i.char_name] = huffman_code;
    }
}

void orgTree::get_encode_result(
    const char *dest_file)
{

    // Look up the huffman code for each character.
    std::ios::sync_with_stdio(false);
    std::string encoded_file_str;
    for (char &i : file_str)
    {
        encoded_file_str += huffman_code_to_char[i];
    }
    std::ofstream outfile_stream(
        dest_file,
        std::ios::out | std::ios::binary);
    if (!outfile_stream)
    {
        throw "failed check: outfile_stream";
    }

    int64_t tree_node_set_size = tree_node_set.size();
    outfile_stream.write(
        (char *)&tree_node_set_size,
        sizeof(int64_t));
    outfile_stream.write(
        (char *)&tree_node_set[0],
        tree_node_set.size() * sizeof(node));
    int64_t encoded_file_str_size = encoded_file_str.size();
    outfile_stream.write(
        (char *)&encoded_file_str_size,
        sizeof(int64_t));

    // Convert a 8-length binary string into a `char`.
    while (encoded_file_str.size() % 8)
    {
        encoded_file_str += '0';
    }
    outfile_stream << binToChar(encoded_file_str);
    outfile_stream.close();
}
