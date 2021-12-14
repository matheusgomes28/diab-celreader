#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::uint32_t read32u_le(std::ifstream &file) {
  std::array<char, 4> bytes;
  file.read(bytes.data(), 4);

  std::uint32_t result;
  std::memcpy(&result, bytes.data(), 4);
  return result;
}

struct CelHeader {
  std::uint32_t cell_frames;
  std::vector<std::uint32_t> frame_offsets;
  std::uint32_t file_size;
};

std::vector<std::uint32_t> read32u_block_le(std::ifstream &file,
                                            std::size_t n = 1) {
  static_assert(sizeof(std::uint32_t) == sizeof(char) * 4);

  std::vector<char> result_bytes;
  result_bytes.resize(n * 4); // is this Ok for all platforms?
  file.read(result_bytes.data(), n * 4);

  std::vector<std::uint32_t> result;
  result.resize(n);
  std::memcpy(result.data(), result_bytes.data(), n * 4);
  return result;
}

// Maybe we need an optional here
// or something
CelHeader read_cell_header(std::string const &file_path) {
  std::ifstream cel_file(file_path, std::ios_base::binary);
  if (!cel_file.good()) {
    // Should probably return an error here
    // or something
    return {};
  }

  std::uint32_t const cell_frames = read32u_le(cel_file);
  std::vector<std::uint32_t> const frame_offsets =
      read32u_block_le(cel_file, cell_frames);
  std::uint32_t const file_size = read32u_le(cel_file);
  return {cell_frames, frame_offsets, file_size};
}

int main() {
  CelHeader header =
      read_cell_header("D:/development/tmp/pngs2cel/cels/test_2cels.cel");
  std::cout << "Number of cell frames: " << header.cell_frames << '\n';

  for (int i = 0; i < header.cell_frames; ++i) {
    std::cout << "Cell Offset (" << i << "): " << header.frame_offsets[i]
              << '\n';
  }

  std::cout << "Finally, the file size: " << header.file_size << '\n';
}
