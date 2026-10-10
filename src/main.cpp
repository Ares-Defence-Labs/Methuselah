#include <methusalah/format/file_manager.hpp>
#include <exception>
#include <iostream>
#include <string_view>

namespace {
void usage() {
    std::cout << "Methusalah 0.1.0 (scaffold)\nUsage: methusalah --help\n"
                 "       methusalah inspect <path>\n";
}
} // namespace
int main(int argc, char* argv[]) {
    if (argc == 1 || (argc == 2 && std::string_view(argv[1]) == "--help")) {
        usage();
        return 0;
    }
    if (argc != 3 || std::string_view(argv[1]) != "inspect") { usage(); return 2; }
    try {
        const auto header = methusalah::format::FileManager{}.read_header(argv[2]);
        std::cout << "Draft container header\nVersion: " << header.version
                  << "\nHeader bytes: " << header.header_size
                  << "\nMetadata bytes: " << header.metadata_size
                  << "\nPayload bytes: " << header.payload_size
                  << "\nPayload validation is not implemented.\n";
    } catch (const std::exception& error) {
        std::cerr << "methusalah: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
