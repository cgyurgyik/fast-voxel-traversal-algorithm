#include "amanatidesWooAlgorithm.h"
#include <numeric>

// Macros defined to avoid unnecessary checks with NaNs when using std::max and std::min
#define MAX(a,b) ((a > b ? a : b))
#define MIN(a,b) ((a < b ? a : b))

void amanatidesWooAlgorithm(const Ray& ray, const Grid3D& grid) noexcept {

    // TODO: Assuming the ray's origin is within the voxel grid. To fix, add Smit's algorithm.
    const value_type tMin = 0.0;
    const value_type tMax = 1.0;
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