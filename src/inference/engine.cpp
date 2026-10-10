#include <methusalah/inference/engine.hpp>
#include <stdexcept>

namespace methusalah::inference {
Engine::Engine(EngineConfig config) : config_(config) {}
void Engine::load_model(const std::filesystem::path&) {
    throw std::logic_error("Model loading is not implemented yet");
}
std::vector<float> Engine::run(std::span<const float>) {
    throw std::logic_error("Inference is not implemented yet");
}
const EngineConfig& Engine::config() const noexcept { return config_; }
} // namespace methusalah::inference
