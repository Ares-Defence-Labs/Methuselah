#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

namespace methusalah::format {
inline constexpr std::array<std::uint8_t, 8> magic = {'M', 'T', 'H', 'S', 'L', 'H', '\r', '\n'};
inline constexpr std::uint16_t current_version = 1;
inline constexpr std::size_t encoded_header_size = 32;

// Logical representation only; never serialize native struct memory.
struct Header {
    std::uint16_t version = current_version;
    std::uint16_t header_size = encoded_header_size;
    std::uint32_t flags = 0;
    std::uint64_t metadata_size = 0;
    std::uint64_t payload_size = 0;
};
using HeaderBytes = std::array<std::byte, encoded_header_size>;

// Invalid/unsupported headers throw std::runtime_error.
void validate(const Header& header);
[[nodiscard]] HeaderBytes encode_header(const Header& header);
[[nodiscard]] Header decode_header(std::span<const std::byte> bytes);
} // namespace methusalah::format
