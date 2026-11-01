#include "echoseek/research_model.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>

namespace {

void write_u16_le(std::span<std::byte> bytes, std::size_t offset, std::uint16_t value) {
    bytes[offset] = static_cast<std::byte>(value & 0xffU);
    bytes[offset + 1] = static_cast<std::byte>((value >> 8U) & 0xffU);
}

void write_u32_le(std::span<std::byte> bytes, std::size_t offset, std::uint32_t value) {
    for (std::size_t index = 0; index < sizeof(value); ++index) {
        bytes[offset + index] =
            static_cast<std::byte>((value >> (index * 8U)) & 0xffU);
    }
}

}  // namespace

int main() {
    using namespace echoseek::public_release;

    std::array<std::byte, 128> synthetic_image{};
    synthetic_image[0] = std::byte{'M'};
    synthetic_image[1] = std::byte{'Z'};
    write_u32_le(synthetic_image, 0x3c, 0x40);
    synthetic_image[0x40] = std::byte{'P'};
    synthetic_image[0x41] = std::byte{'E'};
    write_u16_le(synthetic_image, 0x44, 0x8664);
    write_u16_le(synthetic_image, 0x46, 5);
    write_u16_le(synthetic_image, 0x54, 0x00f0);

    const auto header = inspect_pe_header(synthetic_image);
    assert(header.has_value());
    assert(header->pe_offset == 0x40);
    assert(header->machine == 0x8664);
    assert(header->section_count == 5);
    assert(header->optional_header_size == 0x00f0);

    std::array<std::byte, 256> uniform{};
    assert(shannon_entropy(uniform) == 0.0);

    std::array<std::byte, 256> distributed{};
    for (std::size_t index = 0; index < distributed.size(); ++index) {
        distributed[index] = static_cast<std::byte>(index);
    }
    assert(std::abs(shannon_entropy(distributed) - 8.0) < 0.000001);

    assert(layer_name(visibility_layer::behavioral_correlation) ==
           "behavioral correlation");

    std::cout << "public-safe model checks passed\n";
    return 0;
}
