#ifndef FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H
#define FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H

#include "Ray.h"
#include "Grid3D.h"

// Implements the algorithm presented in Amanatides & Woo's "A Fast Voxel Traversal Algorithm for Ray Tracing."
// See: https://www.researchgate.net/publication/2611491_A_Fast_Voxel_Traversal_Algorithm_for_Ray_Tracing
// If the ray origin is outside the voxel grid, uses a safer version of Smit's ray box intersection algorithm
// to determine intersection. The bounds [t0, t1] determine the begin and end parameter for which the ray travels.
// The algorithm occurs in two phases, initialization and traversal.
// Requires:
//     t0 > t1
//     0.0 <= t0 <= 1.0
//     0.0 <= t1 <= 1.0
//     To encapsulate entire ray traversal, set t0 = 0.0, t1 = 1.0
//     'grid' encapsulates a valid voxel grid system.
//
// Notes:
//     Assumes that indices for voxel coordinates begin at 1.
void amanatidesWooAlgorithm(const Ray& ray, const Grid3D& grid, value_type t0, value_type t1) noexcept;

#endif //FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H
