//
// Created by jay on 01/01/25.
//

#include "../lib/aoc.h"
#include "../lib/assert.h"
#include "day09.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <ranges>
#include <unordered_set>

namespace day09::faster {

ParsedInput parse_input(std::ifstream &input_stream) {
    std::string line;
    std::getline(input_stream, line);

    int file_id = 0;
    int position = 0;

    std::vector<FileBlockV2> file_blocks;
    std::deque<FreeSpaceBlockV2> free_space_blocks;

    for (std::string::size_type i = 0; i < line.size(); i++) {
        bool is_file = i % 2 == 0;

        std::optional<int> size_opt = aoc::ctoi(line[i]);
        aoc_assert(size_opt, "failed to parse size");
        int size = *size_opt;

        if (is_file) {
            file_blocks.emplace_back(position, file_id, size);
            file_id++;
        } else {
            free_space_blocks.emplace_back(position, size);
        }

        position += size;
    }

    return {.file_blocks = file_blocks, .free_space_blocks = free_space_blocks};
}

void print_filesystem(const std::vector<FileBlockV2> &file_blocks, const ParsedInput &input) {
    std::map<int, std::string> fs_map;
    std::unordered_set<int> written_blocks;

    for (const auto &block : file_blocks) {
        written_blocks.insert(block.id);

        for (int i = 0; i < block.size; i++) {
            fs_map[block.position + i] = std::to_string(block.id);
        }
    }

    for (const auto &block : input.free_space_blocks) {
        for (int i = 0; i < block.size; i++) {
            fs_map[block.position + i] = '.';
        }
    }

    for (const auto &block : input.file_blocks) {
        if (written_blocks.contains(block.id)) {
            continue;
        }

        for (int i = 0; i < block.size; i++) {
            fs_map[block.position + i] = std::to_string(block.id);
        }
    }

    std::string output;
    output.reserve(fs_map.size());

    for (const auto &pair : fs_map | std::ranges::views::take(200)) {
        auto [_, display] = pair;
        output += display;
    }

    std::cout << output << std::endl;
}

long calculate_checksum(const std::vector<FileBlockV2> &file_blocks) {
    long result = 0;

    auto blocks_copy = file_blocks;
    std::ranges::sort(blocks_copy, [](const FileBlockV2 &a, const FileBlockV2 &b) {
        return a.position < b.position;
    });

    for (const auto &block : blocks_copy) {
        for (int position = block.position; position < block.position + block.size; position++) {
            result += position * block.id;
        }
    }

    return result;
}

// pass by value as we mutate the input
long part1(ParsedInput input) {
    std::vector<FileBlockV2> moved_file_blocks;
    moved_file_blocks.reserve(input.file_blocks.size());

    for (const auto &file_block : input.file_blocks | std::ranges::views::reverse) {
        aoc_assert(!input.free_space_blocks.empty(), "failed to get free space");

        auto free_space_it = input.free_space_blocks.begin();

        if (free_space_it->position >= file_block.position) {
            // Can't move
            moved_file_blocks.emplace_back(file_block.position, file_block.id, file_block.size);
            continue;
        }

        if (free_space_it->size >= file_block.size) {
            moved_file_blocks.emplace_back(free_space_it->position, file_block.id, file_block.size);

            free_space_it->size -= file_block.size;
            free_space_it->position += file_block.size;

            if (free_space_it->size == 0) {
                input.free_space_blocks.pop_front();
            }
        } else {
            int remaining_size = file_block.size;

            while (remaining_size > 0) {

                if (free_space_it->position >= file_block.position) {
                    moved_file_blocks.emplace_back(file_block.position, file_block.id,
                                                   remaining_size);
                    break;
                }

                auto size = std::min(remaining_size, free_space_it->size);

                moved_file_blocks.emplace_back(free_space_it->position, file_block.id, size);
                remaining_size -= size;

                free_space_it->size -= size;
                free_space_it->position += size;

                if (free_space_it->size == 0) {
                    input.free_space_blocks.pop_front();
                    aoc_assert(!input.free_space_blocks.empty(), "failed to get free space");
                    free_space_it = input.free_space_blocks.begin();
                }
            }
        }
    }

    return calculate_checksum(moved_file_blocks);
}

long part2(ParsedInput input) {
    std::vector<FileBlockV2> moved_file_blocks;
    moved_file_blocks.reserve(input.file_blocks.size());

    for (const auto &file_block : input.file_blocks | std::ranges::views::reverse) {
        aoc_assert(!input.free_space_blocks.empty(), "failed to get free space");
        auto free_space_it = input.free_space_blocks.begin();

        while (free_space_it != input.free_space_blocks.end() &&
               free_space_it->size < file_block.size &&
               free_space_it->position < file_block.position) {
            ++free_space_it;
        }

        if (free_space_it == input.free_space_blocks.end() ||
            free_space_it->position >= file_block.position) {
            // Can't move
            moved_file_blocks.emplace_back(file_block.position, file_block.id, file_block.size);
            continue;
        }

        moved_file_blocks.emplace_back(free_space_it->position, file_block.id, file_block.size);

        free_space_it->size -= file_block.size;
        free_space_it->position += file_block.size;

        if (free_space_it->size == 0) {
            input.free_space_blocks.erase(free_space_it);
        }

        input.free_space_blocks.emplace_back(file_block.position, file_block.size);
    }

    return calculate_checksum(moved_file_blocks);
}

} // namespace day09::faster