#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>

namespace echoseek::public_release {

enum class visibility_layer : std::uint8_t {
    static_artifact,
    reputation_heuristics,
    environment_sandbox,
    telemetry_api,
    native_interception,
    memory_inspection,
    behavioral_correlation,
};

enum class observation : std::uint8_t {
    not_tested,
    observed,
    not_observed,
    detected,
};

struct layer_result {
    visibility_layer layer{};
    observation result{observation::not_tested};
    std::string_view evidence_id{};
    std::string_view limitation{};
};

struct pe_header_summary {
    std::uint32_t pe_offset{};
    std::uint16_t machine{};
    std::uint16_t section_count{};
    std::uint16_t optional_header_size{};
};

[[nodiscard]] constexpr std::string_view layer_name(
    visibility_layer layer) noexcept {
    switch (layer) {
        case visibility_layer::static_artifact:
            return "static artifact analysis";
        case visibility_layer::reputation_heuristics:
            return "reputation and heuristics";
        case visibility_layer::environment_sandbox:
            return "environment and sandbox analysis";
        case visibility_layer::telemetry_api:
            return "telemetry and API observation";
        case visibility_layer::native_interception:
            return "native-call interception";
        case visibility_layer::memory_inspection:
            return "memory-region inspection";
        case visibility_layer::behavioral_correlation:
            return "behavioral correlation";
    }
    return "unknown";
}

[[nodiscard]] std::optional<pe_header_summary> inspect_pe_header(
    std::span<const std::byte> image) noexcept;

[[nodiscard]] double shannon_entropy(
    std::span<const std::byte> bytes) noexcept;

}  // namespace echoseek::public_release
