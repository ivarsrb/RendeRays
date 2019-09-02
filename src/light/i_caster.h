#pragma once
#include <tuple>
#include <util/types.h>

// Interface to light sources used to light the scene.
// Phong shading model is used
namespace light {
class ICaster {
public:
    ICaster(const t::Vec3 ambient, const t::Vec3 diffuse, const t::Vec3 specular);
    // Virtual destructor of a base class ensures that when object
    // is deleted trhough base class pointer both destructors get called.
    virtual ~ICaster() = default;
    const t::Vec3& GetAmbient() const;
    const t::Vec3& GetDiffuse() const;
    const t::Vec3& GetSpecular() const;
    // Get altered diffuse color value that is calculated based on normal
    // vector provided through param
    // If there is only ambient light, this function returns base diffuse color.
    // If light source exists this function is free to implement lighting calculations
    // suited for specific light caster type
    virtual t::Vec3 GetDiffuseLit(const t::Vec3& normal) const;
protected:
    // Ambient color component of the light
    // Can also be thought as global illumination.
    const t::Vec3 ambient_;
    // Diffuse component of light. Can be thought as the color of
    // the light source.
    const t::Vec3 diffuse_;
    // Specular component of light, can be thought as 'shinyness' color.
    const t::Vec3 specular_;
};

}; // light