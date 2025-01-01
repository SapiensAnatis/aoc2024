#ifndef AOC2024_DAY09_H
#define AOC2024_DAY09_H

#include <deque>
#include <fstream>
#include <memory>
#include <vector>

namespace day09 {

enum class BlockType { File, FreeSpace };

class Block {
  public:
    virtual ~Block() = default;
    [[nodiscard]] virtual BlockType get_type() const = 0;
    [[nodiscard]] virtual std::string get_display_string() const = 0;
    virtual bool operator==(const Block &other) = 0;
    bool operator!=(const Block &other);
};

std::ostream &operator<<(std::ostream &stream, const Block &block);

class FreeSpaceBlock : public Block {
  public:
    ~FreeSpaceBlock() override = default;
    [[nodiscard]] BlockType get_type() const override;
    [[nodiscard]] std::string get_display_string() const override;
    bool operator==(const Block &other) override;
};

class FileBlock : public Block {
  public:
    explicit FileBlock(int file_id);
    ~FileBlock() override = default;
    [[nodiscard]] BlockType get_type() const override;
    [[nodiscard]] std::string get_display_string() const override;
    [[nodiscard]] int get_id() const;
    bool operator==(const Block &other) override;

  private:
    int id;
};

struct ParsedInput {
    std::vector<std::shared_ptr<Block>> blocks;
};

ParsedInput parse_input(std::ifstream &input_stream);

long part1(const ParsedInput &input);

long part2(const ParsedInput &input);

} // namespace day09

namespace day09::faster {

struct FileBlockV2 {
    int position;
    int id;
    int size;
};

struct FreeSpaceBlockV2 {
    int position;
    int size;
};

struct ParsedInput {
    std::vector<FileBlockV2> file_blocks;
    std::deque<FreeSpaceBlockV2> free_space_blocks;
};

ParsedInput parse_input(std::ifstream &input_stream);

long part1(ParsedInput input);

long part2(ParsedInput input);

} // namespace day09::faster

#endif // AOC2024_DAY09_H
