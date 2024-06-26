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

#ifndef CUDA_RASTERIZER_H_INCLUDED
#define CUDA_RASTERIZER_H_INCLUDED

#include <vector>
#include <functional>

namespace CudaRasterizer
{
	class Rasterizer
	{
	public:

		static void markVisible(
			int P,
			float* means3D,
			float* viewmatrix,
			float* projmatrix,
			bool* present);

		static int forward(
			std::function<char* (size_t)> geometryBuffer,
			std::function<char* (size_t)> binningBuffer,
			std::function<char* (size_t)> imageBuffer,
			const int P, int D, int M,
			const float* background,
			const int width, int height,
			const float* means3D,
			const float* shs,
			const float* colors_precomp,
			const float* opacities,
			const float* scales,
			const float scale_modifier,
			const float sigma,
			const float* rotations,
			// const float* cov3D_precomp,
			const float* viewmatrix,
			const float* projmatrix,
			const float* cam_pos,
			const float* cam_intr,
			// const float tan_fovx, float tan_fovy,
			const bool prefiltered,
			float* ADD_2,
			float* out_color,
			float* out_depth,
			float* out_normal,
			float* out_opacity,
			float* distort,
			float* radii = nullptr,
			bool debug = false);

		static void backward(
			const int P, int D, int M, int R,
			const float* background,
			const int width, int height,
			const float* means3D,
			const float* shs,
			const float* ADD_2,
			const float* colors_precomp,
			const float* scales,
			const float scale_modifier,
			const float sigma,
			const float* rotations,
			// const float* cov3D_precomp,
			const float* viewmatrix,
			const float* projmatrix,
			const float* campos,
			// const float tan_fovx, float tan_fovy,
			const float* radii,
			char* geom_buffer,
			char* binning_buffer,
			char* image_buffer,
			const float* dL_dpix,
			const float* dL_dout_distort,
			float* dL_dKWH,
			float* dL_dmean2D,
			float* p2_gradient,
			// float* dL_dconic,
			float* dL_dopacity,
			float* dL_dcolor,
			float* dL_dmean3D,
			// float* dL_dcov3D,
			float* dL_dsh,
			float* dL_dscale,
			float* dL_drot,
			bool debug);
	};
};

#endif