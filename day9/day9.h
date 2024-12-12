#ifndef AOC2024_DAY9_H
#define AOC2024_DAY9_H

#include <fstream>
#include <memory>
#include <vector>

namespace day9 {

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

} // namespace day9

#endif // AOC2024_DAY9_H
