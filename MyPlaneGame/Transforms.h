#pragma once

#include <include/glm.h>

namespace Transforms
{
	// Translate matrix
	inline glm::mat4 Translate3D(float translateX, float translateY, float translateZ)
	{
		return glm::transpose(
			glm::mat4(1, 0, 0, translateX,
				0, 1, 0, translateY,
				0, 0, 1, translateZ,
				0, 0, 0, 1));
	}

	// Scale matrix
	inline glm::mat4 Scale3D(float scaleX, float scaleY, float scaleZ)
	{
		return glm::transpose(
			glm::mat4(scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1));
	}

	// Rotate matrix
	inline glm::mat4 RotateOX(float radians)
	{
		return glm::transpose(
			glm::mat4(cos(radians), -sin(radians), 0, 0,
				sin(radians), cos(radians), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1));
	}
	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(1, 0, 0, 0,
				0, cos(radians), -sin(radians), 0,
				0, sin(radians), cos(radians), 0,
				0, 0, 0, 1));
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(cos(radians), 0, sin(radians), 0,
				0, 1, 0, 0,
				-sin(radians), 0, cos(radians), 0,
				0, 0, 0, 1));
	}

}
