#pragma once
#include <filesystem>
#include <methusalah/format/header.hpp>

namespace methusalah::format {
class FileManager {
public:
    // Validates the header only, not metadata or model payloads.
    [[nodiscard]] Header read_header(const std::filesystem::path& path) const;
};
} // namespace methusalah::format
