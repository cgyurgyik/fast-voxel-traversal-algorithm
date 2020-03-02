#ifndef FAST_VOXEL_TRAVERSAL_ALGORITHM_RAY_H
#define FAST_VOXEL_TRAVERSAL_ALGORITHM_RAY_H

#include "Vec3.h"

// Encapsulates the functionality of a ray.
// This consists of two components, the origin of the ray,
// and the direction of the ray.
struct Ray final {
    [[nodiscard]] constexpr Ray(const BoundVec3& origin, const UnitVec3& direction)
            : origin_{origin}, direction_{direction} {}

    // Represents the function p(t) = origin + t * direction,
    // where p is a 3-dimensional position, and t is a scalar.
    [[nodiscard]] inline constexpr BoundVec3 point_at_parameter(const value_type t) const {
        return this->origin_ + (this->direction_ * t);
    }

    [[nodiscard]] inline constexpr BoundVec3 origin() const { return this->origin_; }
    [[nodiscard]] inline constexpr UnitVec3 direction() const { return this->direction_; }
private:
    // The origin of the ray.
    const BoundVec3 origin_;
    // The normalized direction of the ray.
    const UnitVec3 direction_;
};

#endif //FAST_VOXEL_TRAVERSAL_ALGORITHM_RAY_H
