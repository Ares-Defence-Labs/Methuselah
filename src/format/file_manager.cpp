#include <methusalah/format/file_manager.hpp>
#include <fstream>
#include <stdexcept>

namespace methusalah::format {
Header FileManager::read_header(const std::filesystem::path& path) const {
    std::ifstream stream(path, std::ios::binary);
    if (!stream) throw std::runtime_error("Cannot open container: " + path.string());
    HeaderBytes bytes{};
    stream.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    if (!stream) throw std::runtime_error("Cannot read complete header: " + path.string());
    return decode_header(bytes);
}
} // namespace methusalah::format
