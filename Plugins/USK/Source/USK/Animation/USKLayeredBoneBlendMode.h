// Created by Henry Jooste

#pragma once

/**
 * @brief The different modes that can be used to blend animations
 */
UENUM()
enum class EUSKLayeredBoneBlendMode : uint8
{
	/**
	 * @brief Perform the blending using branch filters
	 */
	BranchFilter,

	/**
	 * @brief Perform the blending using a blend mask
	 */
	BlendMask,
};