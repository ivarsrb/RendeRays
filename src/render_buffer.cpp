#include "render_buffer.h"

RenderBuffer::RenderBuffer(uint16_t width, uint16_t height, const t::Vec3& clear_color) :
    width_(width),
    height_(height) {
    // Logically color buffer is 2D but stored as 1D vector
    buffer_.resize(static_cast<size_t>(width) * height);
    Clear(clear_color);
}

void RenderBuffer::PresentTo(const RenderTarget& render_target) const {
    render_target.Write(width_, height_, buffer_);
}

void RenderBuffer::Clear(const t::Vec3& clear_color) {
    std::fill(buffer_.begin(), buffer_.end(), clear_color);
}

uint16_t RenderBuffer::GetWidth() const {
    return width_;
}

uint16_t RenderBuffer::GetHeight() const {
    return height_;
}

void RenderBuffer::SetColor(uint16_t x, uint16_t y, const t::Vec3& color) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_ );
    buffer_.at(x + static_cast<size_t>(y) * width_) = color;
}
