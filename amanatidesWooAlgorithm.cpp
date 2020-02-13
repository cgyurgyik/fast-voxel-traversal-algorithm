#include "amanatidesWooAlgorithm.h"
#include <numeric>

// Macro defined to avoid unnecessary checks with NaNs when using std::max
#define MAX(a,b) ((a > b ? a : b))

// Uses the improved version of Smit's algorithm to determine if the given ray will intersect
// the grid between tMin and tMax. This version causes an additional efficiency penalty,
// but takes into account the negative zero case.
// tMin and tMax are then updated to incorporate the new intersection values.
// See: http://www.cs.utah.edu/~awilliam/box/box.pdf
bool rayBoxIntersection(const Ray& ray, const Grid3D& grid, value_type& tMin, value_type& tMax,
                        value_type t0, value_type t1) {
    value_type tYMin, tYMax, tZMin, tZMax;
    const value_type x_inv_dir = 1 / ray.direction().x();
    if (x_inv_dir >= 0) {
        tMin = (grid.minBound().x() - ray.origin().x()) * x_inv_dir;
        tMax = (grid.maxBound().x() - ray.origin().x()) * x_inv_dir;
    } else {
        tMin = (grid.maxBound().x() - ray.origin().x()) * x_inv_dir;
        tMax = (grid.minBound().x() - ray.origin().x()) * x_inv_dir;
    }

    const value_type y_inv_dir = 1 / ray.direction().y();
    if (y_inv_dir >= 0) {
        tYMin = (grid.minBound().y() - ray.origin().y()) * y_inv_dir;
        tYMax = (grid.maxBound().y() - ray.origin().y()) * y_inv_dir;
    } else {
        tYMin = (grid.maxBound().y() - ray.origin().y()) * y_inv_dir;
        tYMax = (grid.minBound().y() - ray.origin().y()) * y_inv_dir;
    }

    if (tMin > tYMax || tYMin > tMax) return false;
    if (tYMin > tMin) tMin = tYMin;
    if (tYMax < tMax) tMax = tYMax;

    const value_type z_inv_dir = 1 / ray.direction().z();
    if (z_inv_dir >= 0) {
        tZMin = (grid.minBound().z() - ray.origin().z()) * z_inv_dir;
        tZMax = (grid.maxBound().z() - ray.origin().z()) * z_inv_dir;
    } else {
        tZMin = (grid.maxBound().z() - ray.origin().z()) * z_inv_dir;
        tZMax = (grid.minBound().z() - ray.origin().z()) * z_inv_dir;
    }

    if (tMin > tZMax || tZMin > tMax) return false;
    if (tZMin > tMin) tMin = tZMin;
    if (tZMax < tMax) tMax = tZMax;
    return (tMin < t1 && tMax > t0);
}

void amanatidesWooAlgorithm(const Ray& ray, const Grid3D& grid, value_type t0, value_type t1) noexcept {
    value_type tMin; // Modified in rayBoxIntersection.
    value_type tMax; // Modified in rayBoxIntersection.
    const bool ray_has_intersected = rayBoxIntersection(ray, grid, tMin, tMax, t0, t1);
    if (!ray_has_intersected) return;

    tMin = MAX(tMin, t0);
    tMax = MAX(tMax, t1);
    const BoundVec3 ray_start = ray.origin() + ray.direction() * tMin;
    const BoundVec3 ray_end = ray.origin() + ray.direction() * tMax;

    size_t current_X_index = MAX(1, std::ceil(ray_start.x() - grid.minBound().x() / grid.voxelSizeX()));
    const size_t end_X_index = MAX(1, std::ceil(ray_end.x() - grid.minBound().x() / grid.voxelSizeX()));
    int stepX;
    value_type tDeltaX;
    value_type tMaxX;
    if (ray.direction().x() > 0.0) {
        stepX = 1;
        tDeltaX = grid.voxelSizeX() / ray.direction().x();
        tMaxX = tMin + (grid.minBound().x() + current_X_index * grid.voxelSizeX()
                        - ray_start.x()) / ray.direction().x();
    } else if (ray.direction().x() < 0.0) {
        stepX = -1;
        tDeltaX = grid.voxelSizeX() / -ray.direction().x();
        const size_t previous_X_index = current_X_index - 1;
        tMaxX = tMin + (grid.minBound().x() + previous_X_index * grid.voxelSizeX()
                        - ray_start.x()) / ray.direction().x();
    } else {
        stepX = 0;
        tDeltaX = tMax;
        tMaxX = tMax;
    }

    size_t current_Y_index = MAX(1, std::ceil(ray_start.y() - grid.minBound().y() / grid.voxelSizeY()));
    const size_t end_Y_index = MAX(1, std::ceil(ray_end.y() - grid.minBound().y() / grid.voxelSizeY()));
    int stepY;
    value_type tDeltaY;
    value_type tMaxY;
    if (ray.direction().y() > 0.0) {
        stepY = 1;
        tDeltaY = grid.voxelSizeY() / ray.direction().y();
        tMaxY = tMin + (grid.minBound().y() + current_Y_index * grid.voxelSizeY()
                        - ray_start.y()) / ray.direction().y();
    } else if (ray.direction().y() < 0.0) {
        stepY= -1;
        tDeltaY = grid.voxelSizeY() / -ray.direction().y();
        const size_t previous_Y_index = current_Y_index - 1;
        tMaxY = tMin + (grid.minBound().y() + previous_Y_index * grid.voxelSizeY()
                        - ray_start.y()) / ray.direction().y();
    } else {
        stepY = 0;
        tDeltaY = tMax;
        tMaxY = tMax;
    }

    size_t current_Z_index = MAX(1, std::ceil(ray_start.z() - grid.minBound().z() / grid.voxelSizeZ()));
    const size_t end_Z_index = MAX(1, std::ceil(ray_end.z() - grid.minBound().z() / grid.voxelSizeZ()));
    int stepZ;
    value_type tDeltaZ;
    value_type tMaxZ;
    if (ray.direction().z() > 0.0) {
        stepZ = 1;
        tDeltaZ = grid.voxelSizeZ() / ray.direction().z();
        tMaxZ = tMin + (grid.minBound().z() + current_Z_index * grid.voxelSizeZ()
                        - ray_start.z()) / ray.direction().z();
    } else if (ray.direction().z() < 0.0) {
        stepZ = -1;
        tDeltaZ = grid.voxelSizeZ() / -ray.direction().z();
        const size_t previous_Z_index = current_Z_index - 1;
        tMaxZ = tMin + (grid.minBound().z() + previous_Z_index * grid.voxelSizeZ()
                        - ray_start.z()) / ray.direction().z();
    } else {
        stepZ = 0;
        tDeltaZ = tMax;
        tMaxZ = tMax;
    }

    while (current_X_index != end_X_index || current_Y_index != end_Y_index || current_Z_index != end_Z_index) {
        if (tMaxX < tMaxY && tMaxX < tMaxZ) {
            // X-axis traversal.
            current_X_index += stepX;
            tMaxX += tDeltaX;
        } else if (tMaxY < tMaxZ) {
            // Y-axis traversal.
            current_Y_index += stepY;
            tMaxY += tDeltaY;
        } else {
            // Z-axis traversal.
            current_Z_index += stepZ;
            tMaxZ += tDeltaZ;
        }
    }
}