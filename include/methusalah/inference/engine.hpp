#pragma once
#include <cstddef>
#include <filesystem>
#include <span>
#include <vector>

namespace methusalah::inference {
struct EngineConfig {
    // Zero requests automatic worker selection by the future backend.
    std::size_t worker_threads = 0;
};

// Placeholder float buffer API; tensor shapes/types are still to be designed.
class Engine {
public:
    explicit Engine(EngineConfig config = {});
    void load_model(const std::filesystem::path& path);
    [[nodiscard]] std::vector<float> run(std::span<const float> input);
    [[nodiscard]] const EngineConfig& config() const noexcept;
private:
    EngineConfig config_;
};
} // namespace methusalah::inference
