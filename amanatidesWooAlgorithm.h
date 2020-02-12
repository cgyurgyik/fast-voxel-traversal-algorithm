#ifndef FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H
#define FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H

#include "Ray.h"
#include "Grid3D.h"

// Provides a basis for Amanatides & Woo's "A Fast Voxel Traversal Algorithm for Ray Tracing."
// See: https://www.researchgate.net/publication/2611491_A_Fast_Voxel_Traversal_Algorithm_for_Ray_Tracing
// Assumes that indices for voxel coordinates begin at 1.
// If the ray origin is outside the voxel grid, uses Smit's algorithm to determine intersection.
void amanatidesWooAlgorithm(const Ray& ray, const Grid3D& grid) noexcept;

#endif //FAST_VOXEL_TRAVERSAL_ALGORITHM_AMANATIDESWOOALGORITHM_H
