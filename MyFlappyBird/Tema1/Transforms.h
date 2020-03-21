#pragma once

#include <include/glm.h>

namespace Transforms
{
	// Translate matrix
	inline glm::mat4 Translate3D(float translateX, float translateY)
	{
		return glm::transpose(
			glm::mat4(1, 0, 0, translateX,
				0, 1, 0, translateY,
				0, 0, 1, 0,
				0, 0, 0, 1));
	}

	// Scale matrix
	inline glm::mat4 Scale3D(float scaleX, float scaleY)
	{
		return glm::transpose(
			glm::mat4(scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, 1, 0,
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
}
