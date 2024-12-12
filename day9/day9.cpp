#include "day9.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace day9 {

std::ostream &operator<<(std::ostream &stream, const Block &block) {
    stream << block.get_display_string();
    return stream;
}

BlockType FreeSpaceBlock::get_type() const { return BlockType::FreeSpace; }

std::string FreeSpaceBlock::get_display_string() const { return "."; }

FileBlock::FileBlock(int id) : id(id) {}

BlockType FileBlock::get_type() const { return BlockType::File; }

std::string FileBlock::get_display_string() const {
    return std::to_string(this->id);
}

int FileBlock::get_id() const { return this->id; }

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<std::shared_ptr<Block>> blocks;
    int id_counter = 0;

    char next_char;

    while (!input_stream.eof() && !input_stream.fail()) {
        int position = static_cast<int>(input_stream.tellg());
        bool is_file = position % 2 == 0;
        input_stream.get(next_char);

        std::optional<int> block_count = aoc::ctoi(next_char);
        assert(block_count && "Failed to parse block count");

        if (is_file) {
            int file_id = id_counter++;
            for (int i = 0; i < *block_count; i++) {
                auto block = std::make_shared<FileBlock>(file_id);
                blocks.push_back(std::move(block));
            }
        } else {
            for (int i = 0; i < *block_count; i++) {
                auto block = std::make_shared<FreeSpaceBlock>();
                blocks.push_back(std::move(block));
            }
        }
    }

    return {.blocks = std::move(blocks)};
}

void print_filesystem(std::vector<std::shared_ptr<Block>> vec, int start) {

    for (auto it = vec.begin() + start; it != vec.end(); it++) {
        std::cout << **it;
    }

    std::cout << "\n";
}

long part1(const ParsedInput &input) {
    std::vector<std::shared_ptr<Block>> blocks_copy = input.blocks;

    for (auto it = blocks_copy.begin(); it != blocks_copy.end(); it++) {
        if (std::all_of(it, blocks_copy.end(),
                        [](const std::shared_ptr<Block> &block) {
                            return block->get_type() == BlockType::FreeSpace;
                        })) {
            break;
        }

        if ((*it)->get_type() != BlockType::FreeSpace) {
            continue;
        }

        auto file_it =
            std::find_if(blocks_copy.rbegin(), blocks_copy.rend(),
                         [](const std::shared_ptr<Block> &block) {
                             return block->get_type() == BlockType::File;
                         });

        if (file_it != blocks_copy.rend()) {
            std::iter_swap(it, file_it);
        }
    }

    long checksum = 0;
    for (std::vector<Block>::size_type i = 0; i < blocks_copy.size(); i++) {
        auto curr = blocks_copy[i];
        if (auto file_block = std::dynamic_pointer_cast<FileBlock>(curr)) {
            checksum += file_block->get_id() * static_cast<int>(i);
        }
    }

    return checksum;
}

typedef std::vector<std::shared_ptr<Block>>::iterator BlockVectorIterator;
typedef std::vector<std::shared_ptr<Block>>::reverse_iterator
    ReverseBlockVectorIterator;

std::pair<BlockVectorIterator, BlockVectorIterator> greedy_find_if(
    const BlockVectorIterator &start, const BlockVectorIterator &end,
    const std::function<bool(const std::shared_ptr<Block> &)> &predicate) {
    auto it = std::find_if(start, end, predicate);
    if (it == end) {
        return {end, end};
    }

    auto next = it;
    while (next != end && predicate(*next)) {
        next++;
    }

    return {it, next - 1};
}

std::pair<ReverseBlockVectorIterator, ReverseBlockVectorIterator>
greedy_find_file(const ReverseBlockVectorIterator &start,
                 const ReverseBlockVectorIterator &end) {
    auto it = std::find_if(start, end, [](const std::shared_ptr<Block> &block) {
        return block->get_type() == BlockType::File;
    });

    auto start_file_block = std::dynamic_pointer_cast<FileBlock>(*it);
    assert(start_file_block && "greedy_find_file: failed dynamic cast");

    if (it == end) {
        return {end, end};
    }

    auto block_pred = [&start_file_block](const std::shared_ptr<Block> &block) {
        if (block->get_type() != BlockType::File) {
            return false;
        }

        auto file_block = std::dynamic_pointer_cast<FileBlock>(block);
        assert(file_block &&
               "greedy_find_file: failed dynamic cast in block_pred");

        if (file_block->get_id() != start_file_block->get_id()) {
            return false;
        }

        return true;
    };

    auto next = it;
    while (next != end && block_pred(*next)) {
        next++;
    }

    return {it, next - 1};
}

long part2(const ParsedInput &input) {
    std::vector<std::shared_ptr<Block>> blocks_copy = input.blocks;

    auto cursor = blocks_copy.begin();

    while (cursor < blocks_copy.end()) {
        print_filesystem(blocks_copy, 0);

        auto [free_space_start, free_space_end] = greedy_find_if(
            cursor, blocks_copy.end(), [](const std::shared_ptr<Block> &block) {
                return block->get_type() == BlockType::FreeSpace;
            });

        if (free_space_start == blocks_copy.end()) {
            break;
        }

        // If we have two pointers ...
        //                         ^ ^
        //                         A B
        // then B - A = 2, but block size is 3 = B - A + 1
        long free_space_size = free_space_end - free_space_start + 1;

        // std::cout << "Found free space block of length: " << free_space_size
        //           << "\n";

        auto file_cursor = blocks_copy.rbegin();

        while (true) {
            auto [file_start, file_end] =
                greedy_find_file(file_cursor, blocks_copy.rend());

            if (file_start == blocks_copy.rend()) {
                break;
            }

            long file_size = file_end - file_start + 1;

            // std::cout << "Found file block of length: " << file_size << "\n";

            if (file_size > free_space_size) {
                file_cursor = file_end + 1;
                continue;
            }

            std::swap_ranges(free_space_start, free_space_start + file_size,
                             file_start);

            cursor = free_space_start + file_size;

            break;
        }

        cursor++;
    }

    long checksum = 0;
    for (std::vector<Block>::size_type i = 0; i < blocks_copy.size(); i++) {
        auto curr = blocks_copy[i];
        if (auto file_block = std::dynamic_pointer_cast<FileBlock>(curr)) {
            checksum += file_block->get_id() * static_cast<int>(i);
        }
    }

    return checksum;
}

} // namespace day9
