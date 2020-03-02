#ifndef FAST_VOXEL_TRAVERSAL_ALGORITHM_VEC3_H
#define FAST_VOXEL_TRAVERSAL_ALGORITHM_VEC3_H

#include <cmath>

// The type used for the 3-dimensional vectors.
// In most cases, this will be either double or float.
using value_type = double;

// Represents a Euclidean vector in 3-dimensional space.
// Assumes vectors take the form of:
//      [x]
//      [y]
//      [z]
struct Vec3 {
public:
    constexpr explicit Vec3(const value_type x, const value_type y, const value_type z)
            : x_{x}, y_{y}, z_{z} {}

    [[nodiscard]] inline constexpr value_type x() const { return this->x_; }
    [[nodiscard]] inline constexpr value_type y() const { return this->y_; }
    [[nodiscard]] inline constexpr value_type z() const { return this->z_; }

    [[nodiscard]] inline constexpr value_type& x() { return this->x_; }
    [[nodiscard]] inline constexpr value_type& y() { return this->y_; }
    [[nodiscard]] inline constexpr value_type& z() { return this->z_; }

    [[nodiscard]] inline value_type length() const {
        return std::hypot(this->x(), this->y(), this->z());
    }

    [[nodiscard]] inline value_type squared_length() const {
        return x() * x() + y() * y() + z() * z();
    }

private:
    // Represents the x-dimension value of the vector.
    value_type x_;
    // Represents the y-dimension value of the vector.
    value_type y_;
    // Represents the z-dimension value of the vector.
    value_type z_;
};

// A 3-dimensional free vector, which has no initial point. It has two main criteria:
// (1) direction, and (2) magnitude.
struct FreeVec3 final : Vec3 {
    using Vec3::Vec3;

    [[nodiscard]] constexpr explicit FreeVec3(const Vec3& vec3) : Vec3::Vec3{vec3} {}

    [[nodiscard]] inline constexpr value_type dot(const Vec3& other) const {
        return this->x() * other.x() + this->y() * other.y() + this->z() * other.z();
    }

    [[nodiscard]] inline constexpr FreeVec3 cross(const Vec3& other) const {
        return FreeVec3{this->y() * other.z() - this->z() * other.y(),
                        this->z() * other.x() - this->x() * other.z(),
                        this->x() * other.y() - this->y() * other.x()};
    }

    [[nodiscard]] inline constexpr FreeVec3& operator+=(const FreeVec3& other) {
        this->x() += other.x();
        this->y() += other.y();
        this->z() += other.z();
        return *this;
    }

    [[nodiscard]] inline constexpr FreeVec3& operator-=(const FreeVec3& other) {
        this->x() -= other.x();
        this->y() -= other.y();
        this->z() -= other.z();
        return *this;
    }

    [[nodiscard]]  inline constexpr FreeVec3& operator*=(const value_type scalar) {
        this->x() *= scalar;
        this->y() *= scalar;
        this->z() *= scalar;
        return *this;
    }

    [[nodiscard]] inline constexpr FreeVec3& operator/=(const value_type scalar) {
        this->x() /= scalar;
        this->y() /= scalar;
        this->z() /= scalar;
        return *this;
    }
};

[[nodiscard]] inline constexpr FreeVec3 operator+(const FreeVec3& v) { return v; }

[[nodiscard]] inline constexpr FreeVec3 operator-(const FreeVec3& v) {
    return FreeVec3{-v.x(), -v.y(), -v.z()};
}

[[nodiscard]] inline constexpr FreeVec3 operator+(FreeVec3 v1, const FreeVec3& v2) {
    return v1 += v2;
}

[[nodiscard]] inline constexpr FreeVec3 operator-(FreeVec3 v1, const FreeVec3& v2) {
    return v1 -= v2;
}

[[nodiscard]] inline constexpr FreeVec3 operator*(FreeVec3 v, const value_type scalar) {
    return v *= scalar;
}

[[nodiscard]] inline constexpr FreeVec3 operator/(FreeVec3 v, const value_type scalar) {
    return v /= scalar;
}

// A 3-dimensional bounded vector has a fixed start and end point. It represents a fixed point
// in space, relative to some frame of reference.
struct BoundVec3 final : Vec3 {
    [[nodiscard]]constexpr explicit BoundVec3(const Vec3& vec3) : Vec3::Vec3{vec3} {}

    [[nodiscard]] inline constexpr value_type dot(const Vec3& other) const {
        return this->x() * other.x() + this->y() * other.y() + this->z() * other.z();
    }

    [[nodiscard]] inline constexpr BoundVec3& operator+=(const FreeVec3& other) {
        this->x() += other.x();
        this->y() += other.y();
        this->z() += other.z();
        return *this;
    }

    [[nodiscard]] inline constexpr BoundVec3& operator-=(const FreeVec3& other) {
        return *this += (-other);
    }
};

[[nodiscard]] inline constexpr FreeVec3 operator-(const BoundVec3& v1, const BoundVec3& v2) {
    return FreeVec3{v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z()};
}

[[nodiscard]] inline constexpr BoundVec3 operator+(BoundVec3 v1, const FreeVec3& v2) {
    return v1 += v2;
}

[[nodiscard]] inline constexpr BoundVec3 operator-(BoundVec3 v1, const FreeVec3& v2) {
    return v1 -= v2;
}

// Represents a 3-dimensional unit vector, an abstraction over free vectors that guarantees
// a length of 1. To prevent its length from changing, UnitVec3 does not allow
// for mutations.
struct UnitVec3 final {
    UnitVec3(value_type x, value_type y, value_type z)
            : UnitVec3{FreeVec3{x, y, z}} {}
    [[nodiscard]] constexpr explicit UnitVec3(const Vec3& vec3) : UnitVec3{FreeVec3{vec3}} {}
    [[nodiscard]] constexpr explicit UnitVec3(const FreeVec3& free_vec3) :
    inner_{free_vec3 / free_vec3.length()} {}

    [[nodiscard]] inline constexpr value_type x() const { return this->to_free().x(); }
    [[nodiscard]] inline constexpr value_type y() const { return this->to_free().y(); }
    [[nodiscard]] inline constexpr value_type z() const { return this->to_free().z(); }
    [[nodiscard]] inline constexpr const FreeVec3& to_free() const { return inner_; }
private:
    const FreeVec3 inner_;
};

[[nodiscard]] inline constexpr FreeVec3 operator*(const UnitVec3& v, const value_type scalar) {
    return v.to_free() * scalar;
}

[[nodiscard]] inline constexpr FreeVec3 operator/(const UnitVec3& v, const value_type scalar) {
    return v.to_free() / scalar;
}

#endif //FAST_VOXEL_TRAVERSAL_ALGORITHM_VEC3_H
