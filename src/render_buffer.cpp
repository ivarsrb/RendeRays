#include "render_buffer.h"

RenderBuffer::RenderBuffer(const t::Size16& dimensions, const t::Vec3& clear_color) :
    dimensions_(dimensions) {
    // Logically color buffer is 2D but stored as 1D vector
    buffer_.resize(static_cast<size_t>(dimensions_.width) * dimensions_.height);
    Clear(clear_color);
}

void RenderBuffer::PresentTo(const RenderTarget& render_target) const {
    render_target.Write(buffer_, dimensions_);
}

void RenderBuffer::Clear(const t::Vec3& clear_color) {
    std::fill(buffer_.begin(), buffer_.end(), clear_color);
}

t::U16 RenderBuffer::GetWidth() const {
    return dimensions_.width;
}

t::U16 RenderBuffer::GetHeight() const {
    return dimensions_.height;
}

void RenderBuffer::SetColor(const t::Vec2u16& pixel, const t::Vec3& color) {
    assert(pixel.x >= 0 && pixel.x < dimensions_.width && pixel.y >= 0 && pixel.y < dimensions_.height );
    buffer_.at(pixel.x + static_cast<size_t>(pixel.y) * dimensions_.width) = color;
}
