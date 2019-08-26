#pragma once
#include <vector>
#include "util/types.h"
#include "render_target.h"

// Stores color data of the final render
class RenderBuffer {
public:
    RenderBuffer(const t::Size16& dimensions, const t::Vec3& clear_color);
    // Write contents of a color buffer to given rendering target
    void PresentTo(const RenderTarget& render_target) const;
    // Fill colorbuffer with given color
    void Clear(const t::Vec3& clear_color);
    t::U16 GetWidth() const;
    t::U16 GetHeight() const;
    // Set given color in given coordinates of a buffer
    // x and y gor from 0 to width - 1 and height - 1
    void SetColor(const t::Vec2u16 &pixel, const t::Vec3& color);
private:
    // Dimension of color buffer
    const t::Size16 dimensions_;
    // Color buffer where final scene render is stored
    // Colors are stored as RGB floats in a range 0.0 - 1.0
    t::ColorBuffer buffer_;
};