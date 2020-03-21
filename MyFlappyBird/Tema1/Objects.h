#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{
	Mesh* CreateSquare(std::string name, short diff);
	Mesh* CreateBird(std::string name, glm::vec3 color, glm::vec3 wing_color, short flying);
	Mesh* CreateCloud(std::string name);
	Mesh* CreateGround(std::string name);
	Mesh* CreateStars(std::string name);
	Mesh* CreateSun(std::string name);
}

