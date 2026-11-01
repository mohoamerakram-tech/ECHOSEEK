#include "echoseek/research_model.hpp"

#include <array>
#include <cmath>
#include <limits>

namespace echoseek::public_release {
namespace {

[[nodiscard]] bool range_available(
    std::span<const std::byte> bytes,
    std::size_t offset,
    std::size_t length) noexcept {
    return offset <= bytes.size() && length <= bytes.size() - offset;
}

[[nodiscard]] std::optional<std::uint16_t> read_u16_le(
    std::span<const std::byte> bytes,
    std::size_t offset) noexcept {
    if (!range_available(bytes, offset, sizeof(std::uint16_t))) {
        return std::nullopt;
    }

    const auto b0 = std::to_integer<std::uint16_t>(bytes[offset]);
    const auto b1 = std::to_integer<std::uint16_t>(bytes[offset + 1]);
    return static_cast<std::uint16_t>(b0 | (b1 << 8U));
}

[[nodiscard]] std::optional<std::uint32_t> read_u32_le(
    std::span<const std::byte> bytes,
    std::size_t offset) noexcept {
    if (!range_available(bytes, offset, sizeof(std::uint32_t))) {
        return std::nullopt;
    }

    std::uint32_t value = 0;
    for (std::size_t index = 0; index < sizeof(value); ++index) {
        value |= std::to_integer<std::uint32_t>(bytes[offset + index])
                 << (index * 8U);
    }
    return value;
}

}  // namespace

std::optional<pe_header_summary> inspect_pe_header(
    std::span<const std::byte> image) noexcept {
    constexpr std::size_t pe_pointer_offset = 0x3c;
    constexpr std::size_t coff_header_offset = 0x04;

    if (!range_available(image, 0, 2) ||
        image[0] != std::byte{'M'} || image[1] != std::byte{'Z'}) {
        return std::nullopt;
    }

    const auto pe_offset = read_u32_le(image, pe_pointer_offset);
    if (!pe_offset || *pe_offset > std::numeric_limits<std::uint32_t>::max() - 24U) {
        return std::nullopt;
    }

    const auto signature_offset = static_cast<std::size_t>(*pe_offset);
    if (!range_available(image, signature_offset, 24) ||
        image[signature_offset] != std::byte{'P'} ||
        image[signature_offset + 1] != std::byte{'E'} ||
        image[signature_offset + 2] != std::byte{0} ||
        image[signature_offset + 3] != std::byte{0}) {
        return std::nullopt;
    }

    const auto machine = read_u16_le(image, signature_offset + coff_header_offset);
    const auto sections = read_u16_le(image, signature_offset + coff_header_offset + 2);
    const auto optional_size = read_u16_le(image, signature_offset + coff_header_offset + 16);

    if (!machine || !sections || !optional_size) {
        return std::nullopt;
    }

    return pe_header_summary{
        .pe_offset = *pe_offset,
        .machine = *machine,
        .section_count = *sections,
        .optional_header_size = *optional_size,
    };
}

double shannon_entropy(std::span<const std::byte> bytes) noexcept {
    if (bytes.empty()) {
        return 0.0;
    }

    std::array<std::size_t, 256> frequencies{};
    for (const auto value : bytes) {
        ++frequencies[std::to_integer<std::uint8_t>(value)];
    }

    const auto count = static_cast<double>(bytes.size());
    double entropy = 0.0;
    for (const auto frequency : frequencies) {
        if (frequency == 0) {
            continue;
        }
        const auto probability = static_cast<double>(frequency) / count;
        entropy -= probability * std::log2(probability);
    }
    return entropy;
}

}  // namespace echoseek::public_release
