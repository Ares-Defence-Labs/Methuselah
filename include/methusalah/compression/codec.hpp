#pragma once
#include <cstddef>
#include <span>
#include <string_view>
#include <vector>

namespace methusalah::compression {
struct EncodedData {
    std::vector<std::byte> bytes;
    std::size_t original_size = 0;
};

// Initial lossless byte codec interface; model quantization needs tensor metadata.
class Codec {
public:
    virtual ~Codec() = default;
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
    [[nodiscard]] virtual EncodedData compress(std::span<const std::byte> input) const = 0;
    [[nodiscard]] virtual std::vector<std::byte> decompress(
        const EncodedData& input, std::size_t max_output_size) const = 0;
};
} // namespace methusalah::compression
