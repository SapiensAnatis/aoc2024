#include "day09.h"
#include "../lib/aoc.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

namespace day9 {

std::ostream &operator<<(std::ostream &stream, const Block &block) {
    stream << block.get_display_string();
    return stream;
}

bool Block::operator!=(const Block &other) { return !(*this == other); }

BlockType FreeSpaceBlock::get_type() const { return BlockType::FreeSpace; }

std::string FreeSpaceBlock::get_display_string() const { return "."; }

bool FreeSpaceBlock::operator==(const Block &other) {
    return other.get_type() == BlockType::FreeSpace;
}

FileBlock::FileBlock(int id) : id(id) {}

BlockType FileBlock::get_type() const { return BlockType::File; }

std::string FileBlock::get_display_string() const { return std::to_string(this->id); }

int FileBlock::get_id() const { return this->id; }

bool FileBlock::operator==(const Block &other) {
    if (other.get_type() == BlockType::FreeSpace) {
        return false;
    }

    auto file_other = dynamic_cast<const FileBlock &>(other);
    return this->get_id() == file_other.get_id();
}

ParsedInput parse_input(std::ifstream &input_stream) {
    std::vector<std::shared_ptr<Block>> blocks;
    int id_counter = 0;

    std::vector<char> input_vec = {std::istream_iterator<char>(input_stream),
                                   std::istream_iterator<char>()};

    for (std::vector<char>::size_type i = 0; i < input_vec.size(); i++) {
        bool is_file = i % 2 == 0;

        std::optional<int> block_count = aoc::ctoi(input_vec[i]);
        assert(block_count && "Failed to parse block count");

        if (is_file) {
            int file_id = id_counter++;
            for (int j = 0; j < *block_count; j++) {
                auto block = std::make_shared<FileBlock>(file_id);
                blocks.push_back(std::move(block));
            }
        } else {
            for (int j = 0; j < *block_count; j++) {
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

    std::cout << std::endl;
}

long part1(const ParsedInput &input) {
    std::vector<std::shared_ptr<Block>> blocks_copy = input.blocks;

    for (auto it = blocks_copy.begin(); it != blocks_copy.end(); it++) {
        if (std::all_of(it, blocks_copy.end(), [](const std::shared_ptr<Block> &block) {
                return block->get_type() == BlockType::FreeSpace;
            })) {
            break;
        }

        if ((*it)->get_type() != BlockType::FreeSpace) {
            continue;
        }

        auto file_it = std::find_if(blocks_copy.rbegin(), blocks_copy.rend(),
                                    [](const std::shared_ptr<Block> &block) {
                                        return block->get_type() == BlockType::File;
                                    });

        if (file_it != blocks_copy.rend()) {
            std::iter_swap(it, file_it);
        }
    }

    long checksum = 0;
    for (std::vector<Block>::size_type i = 0; i < blocks_copy.size(); i++) {
        const auto &curr = blocks_copy[i];
        if (auto file_block = std::dynamic_pointer_cast<FileBlock>(curr)) {
            checksum += file_block->get_id() * static_cast<int>(i);
        }
    }

    return checksum;
}

struct ContiguousFile {
    std::shared_ptr<FileBlock> block;
    int position;
    int size;

    ContiguousFile(std::shared_ptr<FileBlock> block, int position, int size)
        : block(std::move(block)), position(position), size(size) {}
};

long part2(const ParsedInput &input) {
    auto blocks_copy = input.blocks;
    std::vector<ContiguousFile> contiguous_blocks;

    print_filesystem(input.blocks, 0);

    for (auto it = input.blocks.begin(); it != input.blocks.end();) {
        if ((*it)->get_type() != BlockType::File) {
            it++;
            continue;
        }

        auto region_end = std::find_if(
            it, input.blocks.end(), [&it](const std::shared_ptr<Block> &x) { return *x != **it; });

        long contig_size = region_end - it;
        long position = it - input.blocks.begin();

        auto ptr = std::dynamic_pointer_cast<FileBlock>(*it);

        assert(ptr && "FileBlock dynamic cast failed");

        contiguous_blocks.emplace_back(ptr, position, contig_size);

        std::cout << "Contiguous block: " << **it << " of size " << contig_size << " at position "
                  << position << std::endl;

        it += contig_size;
    }

    for (const auto &contiguous_block : std::ranges::reverse_view(contiguous_blocks)) {
        //        std::cout << "Attempting to move block " <<
        //        *contiguous_block.block
        //                  << " of size " << contiguous_block.size <<
        //                  std::endl;

        auto is_free_space = [](const std::shared_ptr<Block> &block) {
            return block->get_type() == BlockType::FreeSpace;
        };

        auto space_search_iter = blocks_copy.begin();
        while (space_search_iter != blocks_copy.end() &&
               space_search_iter - blocks_copy.begin() < contiguous_block.position) {
            auto space_iter = std::find_if(space_search_iter, blocks_copy.end(), is_free_space);

            long space_position = space_iter - blocks_copy.begin();
            if (space_position >= contiguous_block.position) {
                break;
            }

            auto space_end_iter = space_iter;

            while (space_end_iter != blocks_copy.end() && is_free_space(*space_end_iter)) {
                space_end_iter++;
            }

            long space_size = space_end_iter - space_iter;
            int file_size = contiguous_block.size;

            //            std::cout << "Found free space of size " << space_size
            //            << std::endl;

            if (space_size >= file_size) {
                //                std::cout << "Performing swap\n";

                std::swap_ranges(space_iter, space_iter + file_size,
                                 blocks_copy.begin() + contiguous_block.position);
                //                print_filesystem(blocks_copy, 0);
                break;

            } else {
                // std::cout << "Space was not sufficient\n";
                space_search_iter = space_end_iter;
                continue;
            }
        }
    }

    long checksum = 0;
    for (std::vector<Block>::size_type i = 0; i < blocks_copy.size(); i++) {
        const auto &curr = blocks_copy[i];
        if (auto file_block = std::dynamic_pointer_cast<FileBlock>(curr)) {
            checksum += file_block->get_id() * static_cast<int>(i);
        }
    }

    return checksum;
}

} // namespace day9
