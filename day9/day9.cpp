#include "day9.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
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

} // namespace day9
