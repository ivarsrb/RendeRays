#include "sphere.h"
#include <algorithm>
#include <stdexcept>

namespace renderable {
Sphere::Sphere(const t::Vec3& center, t::F32 radius, const t::Vec3& color) :
    IRenderable(color),
    center_(center),
    radius_(radius) {
}

// When false is returned 'distance' is unmodified
bool Sphere::Intersect(const Ray& ray, Hit& hit) const {
    // Solutions to equation
    // There are two since it is a quadratic equation
    t::F32 solution_0;
    t::F32 solution_1;
    // Geometric
    bool intersected = IntersectGeometric(ray, solution_0, solution_1);
    // Analytic
    //bool intersected = IntersectAnalytic(ray, solution_0, solution_1);
    // Choose which solution is the hit distance
    if (intersected) {
        // Let the t0 be the smallest one
        if (solution_0 > solution_1) {
            std::swap(solution_0, solution_1);
        }
        // If the smallest solution is non-negative, let it be the distance
        if (solution_0 >= 0) {
            hit.SetDistance(solution_0);
            // Calculate surface normal
            hit.SetSurfaceNormal(GetNormal(ray.GetPoint(solution_0)));
        }
        // If  smallest solution is negative, let the solution be the biggest one
        else if (solution_1 >= 0) {
            hit.SetDistance(solution_1);
            // Calculate surface normal
            hit.SetSurfaceNormal(GetNormal(ray.GetPoint(solution_1)));
        }
        // Both solutions are negative, sphere is behind ray origin
        else {
            return false;
        }
    }
    return intersected;
}

const t::Vec3& Sphere::GeCenter() const {
    return center_;
}

t::F32 Sphere::GetRadius() const {
    return radius_;
}

// Geometric solution to ray-sphere intersection problem.
// t0 and t1 are solutions to equation.
// Does not return parameters if result is false (no solutions).
bool Sphere::IntersectGeometric(const Ray& ray, t::F32& t0, t::F32& t1) const {
    // Get vector from the origin of ray to center o the sphere
    t::Vec3 link = center_ - ray.GetOrigin();
    t::F32 tca = glm::dot(link, ray.GetDirection());
    // If this dot product is negative it means ray direction vector and origin-center vector are
    // in oposite directions and cann not be hit.
    // NOTE: this commented out because it wrongly discards case where center of a spehere
    // is behind ray origin, but radius is big enaigh to cover rays origin and it should be visible
    // if (tca < 0) {
    //    return false;
    // }
    // Check squared distance from center to ray to see if it overshot the sphere
    // (Pythagoras theorem here)
    t::F32 dist_2 = glm::dot(link, link) - tca * tca;
    // If distance (squared because no need to root and is faster) 
    // is bigger than radius tha ray doesnt ht (overshoot)
    if (dist_2 > radius_ * radius_) {
        return false;
    }
    // In final part get the intersection points of a ray and sphere
    t::F32 thc = sqrt(radius_ * radius_ - dist_2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

// Analytic approach using quadratic equation solver
bool Sphere::IntersectAnalytic(const Ray& ray, t::F32& t0, t::F32& t1) const {
    // Get vector from the center of ray to origin o the sphere
    t::Vec3 link = ray.GetOrigin() - center_;
    // Calculate the members of quadratic equation
    t::F32 a = glm::dot(ray.GetDirection(), ray.GetDirection());
    t::F32 b = 2 * glm::dot(ray.GetDirection(), link);
    t::F32 c = glm::dot(link, link) - radius_ * radius_;
    return SolveQuadratic(a, b, c, t0, t1);
}

// General function to solve quadratic equation
// Returns false of no solutions found
bool Sphere::SolveQuadratic(t::F32 a, t::F32 b, t::F32 c, t::F32& x0, t::F32& x1) const {
    // Discriminnant
    t::F32 discr = b * b - 4 * a * c;
    // No solution
    if (discr < 0) {
        return false;
    }
    // One solution
    else if (discr == 0) {
        x0 = x1 = -0.5f * b / a;
    }
    // Two solutions
    else {
        t::F32 q = (b > 0) ? -0.5f * (b + sqrt(discr)) :
            -0.5f * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }

    return true;
}

// It is ok for returned value to not be optimised
t::Vec3 Sphere::GetNormal(const t::Vec3& point_on_surface) const {
    return point_on_surface - center_;
}
}; //renderable

