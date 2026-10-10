#include <methusalah/format/header.hpp>
#include <limits>
#include <stdexcept>

namespace methusalah::format {
namespace {
void write_le(HeaderBytes& bytes, std::size_t offset, std::uint64_t value, std::size_t width) {
    for (std::size_t i = 0; i < width; ++i)
        bytes[offset + i] = static_cast<std::byte>((value >> (8 * i)) & 0xff);
}
std::uint64_t read_le(std::span<const std::byte> bytes, std::size_t offset, std::size_t width) {
    std::uint64_t value = 0;
    for (std::size_t i = 0; i < width; ++i)
        value |= std::to_integer<std::uint64_t>(bytes[offset + i]) << (8 * i);
    return value;
}
} // namespace

void validate(const Header& header) {
    if (header.version != current_version) throw std::runtime_error("Unsupported container version");
    if (header.header_size != encoded_header_size) throw std::runtime_error("Invalid header size");
    if (header.flags != 0) throw std::runtime_error("Unsupported container flags");
    const auto available = std::numeric_limits<std::uint64_t>::max() - header.header_size;
    if (header.metadata_size > available || header.payload_size > available - header.metadata_size)
        throw std::runtime_error("Container size fields overflow");
}
HeaderBytes encode_header(const Header& header) {
    validate(header);
    HeaderBytes bytes{};
    for (std::size_t i = 0; i < magic.size(); ++i) bytes[i] = static_cast<std::byte>(magic[i]);
    write_le(bytes, 8, header.version, 2);
    write_le(bytes, 10, header.header_size, 2);
    write_le(bytes, 12, header.flags, 4);
    write_le(bytes, 16, header.metadata_size, 8);
    write_le(bytes, 24, header.payload_size, 8);
    return bytes;
}
Header decode_header(std::span<const std::byte> bytes) {
    if (bytes.size() != encoded_header_size) throw std::runtime_error("Expected a 32-byte header");
    for (std::size_t i = 0; i < magic.size(); ++i)
        if (bytes[i] != static_cast<std::byte>(magic[i])) throw std::runtime_error("Invalid container magic");
    Header header{static_cast<std::uint16_t>(read_le(bytes, 8, 2)),
                  static_cast<std::uint16_t>(read_le(bytes, 10, 2)),
                  static_cast<std::uint32_t>(read_le(bytes, 12, 4)),
                  read_le(bytes, 16, 8), read_le(bytes, 24, 8)};
    validate(header);
    return header;
}
} // namespace methusalah::format
