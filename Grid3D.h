#ifndef FAST_VOXEL_TRAVERSAL_ALGORITHM_GRID3D_H
#define FAST_VOXEL_TRAVERSAL_ALGORITHM_GRID3D_H

#include <cstddef>
#include "Vec3.h"

// Represents a 3 dimensional grid sub-divided with voxels. Provides necessary information to perform
// traversal over the grid system.
//
// Requires:
//   min_bound < max_bound
//   num_x_voxels > 0
//   num_y_voxels > 0
//   num_z_voxels > 0
struct Grid3D {
public:
    [[nodiscard]] constexpr Grid3D(const BoundVec3& min_bound, const BoundVec3& max_bound, size_t num_x_voxels,
            size_t num_y_voxels, size_t num_z_voxels) :
            min_bound_{min_bound},
            max_bound_{max_bound_},
            grid_size_{max_bound - min_bound},
            num_x_voxels_{num_x_voxels_},
            num_y_voxels_{num_y_voxels},
            num_z_voxels_{num_z_voxels},
            voxel_size_x_{grid_size_.x() / num_x_voxels},
            voxel_size_y_{grid_size_.y() / num_y_voxels},
            voxel_size_z_{grid_size_.z() / num_z_voxels} {}

    [[nodiscard]] constexpr inline size_t numberOfXVoxels() const { return num_x_voxels_; }
    [[nodiscard]] constexpr inline size_t numberOfYVoxels() const { return num_y_voxels_; }
    [[nodiscard]] constexpr inline size_t numberOfZVoxels() const { return num_z_voxels_; }
    [[nodiscard]] constexpr inline BoundVec3 minBound() const { return min_bound_; }
    [[nodiscard]] constexpr inline BoundVec3 maxBound() const { return max_bound_; }
    [[nodiscard]] constexpr inline FreeVec3 gridSize() const { return grid_size_; }
    [[nodiscard]] constexpr inline value_type voxelSizeX() const { return voxel_size_x_; }
    [[nodiscard]] constexpr inline value_type voxelSizeY() const { return voxel_size_y_; }
    [[nodiscard]] constexpr inline value_type voxelSizeZ() const { return voxel_size_z_; }

private:
    // The minimum bound vector of the voxel grid.
    const BoundVec3 min_bound_;
    // The maximum bound vector of the voxel grid.
    const BoundVec3 max_bound_;
    // The grid size, determined by (max_bound_ - min_bound_).
    const FreeVec3 grid_size_;
    // The number of voxels in each of the x, y, z directions.
    const size_t num_x_voxels_, num_y_voxels_, num_z_voxels_;
    // The size of the voxel's x dimension.
    const value_type voxel_size_x_;
    // The size of the voxel's y dimension.
    const value_type voxel_size_y_;
    // The size of the voxel's z dimension.
    const value_type voxel_size_z_;
};

#endif //FAST_VOXEL_TRAVERSAL_ALGORITHM_GRID3D_H
