#pragma once
#include <ray.h>

// Interface to renderable objects that the ray tracer can render
namespace renderable {
class IRenderable {
public:
    IRenderable(const t::Vec3& color);
    // Virtual destructor of a base class ensures that when object
    // is deleted trhough base class pointer both destructors get called.
    virtual ~IRenderable() = default;
    // Ray - renderable object intersection test
    // Return weather ray intersetcs the renderable 
    // and distance from ray origin to hit point.
    virtual bool Intersect(const Ray& ray, t::F32& distance) const = 0;
    const t::Vec3& GetColor() const;
protected:
    const t::Vec3 color_;
};
}; // renderable