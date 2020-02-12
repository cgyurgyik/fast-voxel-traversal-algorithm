cmake_minimum_required(VERSION 3.15)
project(fast_voxel_traversal_algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(fast_voxel_traversal_algorithm amanatidesWooAlgorithm.cpp amanatidesWooAlgorithm.h Ray.h Vec3.h Grid3D.h)