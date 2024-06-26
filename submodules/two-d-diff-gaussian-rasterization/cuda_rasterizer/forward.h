/*
 * Copyright (C) 2023, Inria
 * GRAPHDECO research group, https://team.inria.fr/graphdeco
 * All rights reserved.
 *
 * This software is free for non-commercial, research and evaluation use 
 * under the terms of the LICENSE.md file.
 *
 * For inquiries contact  george.drettakis@inria.fr
 */

#ifndef CUDA_RASTERIZER_FORWARD_H_INCLUDED
#define CUDA_RASTERIZER_FORWARD_H_INCLUDED

#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define GLM_FORCE_CUDA
#include <glm/glm.hpp>

namespace FORWARD
{
	// Perform initial steps for each Gaussian prior to rasterization.
	void preprocess(int P, int D, int M,
		const float* orig_points,
		const glm::vec3* scales,
		const float scale_modifier,
		const float sigma,
		const glm::vec4* rotations,
		const float* opacities,
		const float* shs,
		bool* clamped,
		// const float* cov3D_precomp,
		const float* colors_precomp,
		const glm::mat4* viewmatrix,
		const glm::mat3* projmatrix,
		const glm::vec3* cam_pos,
		const float* cam_intr,
		const int W, int H,
		// const float focal_x, float focal_y,
		// const float tan_fovx, float tan_fovy,
		float* radii,
		float2* points_xy_image,
		float* depths,
		float* normals,
		glm::mat3x3* KWH,
		// float* cov3Ds,
		float* rgb,
		float4* conic_opacity,
		const dim3 grid,
		uint32_t* tiles_touched,
		bool prefiltered);

	// Main rasterization method.
	void render(
		const dim3 grid, dim3 block,
		const uint2* ranges,
		const uint32_t* point_list,
		int W, int H,
		const float2* points_xy_image,
		const float* means3D,
		const float sigma,
		const float* depths,
		const float* normals,
		// const float* cam_intr,
		// const glm::vec4* quaternions,
		// const glm::vec3* scales,
		const glm::mat3x3* KWH,
		const float* colors,
		const float4* conic_opacity,
		glm::vec3* ADD_2,
		float* final_T,
		uint32_t* n_contrib,
		const float* bg_color,
		float* out_color,
		float* out_depth,
		float* out_normal,
		float* out_opacity,
		float* distort);
}


#endif