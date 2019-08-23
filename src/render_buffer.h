#pragma once
#include <vector>
#include "types.h"
#include "render_target.h"

// Stores color data of the final render
class RenderBuffer {
public:
    RenderBuffer(uint16_t width, uint16_t height, const t::Vec3& clear_color);
    // Write contents of a color buffer to given rendering target
    void PresentTo(const RenderTarget& render_target) const;
    // Fill colorbuffer with given color
    void Clear(const t::Vec3& clear_color);
    uint16_t GetWidth() const;
    uint16_t GetHeight() const;
    // Set given color in given coordinates of a buffer
    // x and y gor from 0 to width - 1 and height - 1
    void SetColor(uint16_t x, uint16_t y, const t::Vec3& color);
private:
    // Dimension of color buffer
    const uint16_t width_;
    const uint16_t height_;
    // Color buffer where final scene render is stored
    // Colors are stored as RGB floats in a range 0.0 - 1.0
    t::ColorBuffer buffer_;
};