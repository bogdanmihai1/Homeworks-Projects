#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{
	Mesh* CreateCloud(std::string name);
	Mesh* CreateGround(std::string name);
	Mesh* PlaneBody(std::string name);
	Mesh* PlanePropeller(std::string name);
	Mesh* PilotHair(std::string name);
	Mesh* CreateSmoke(std::string name);
	Mesh* CreateWhiteBox(std::string name);
	Mesh* CreateLives(std::string name);
	Mesh* CreateObstacle(std::string name);
	Mesh* CreateFuel(std::string name);
	Mesh* CreateFuelBar1(std::string name);
	Mesh* CreateFuelBar2(std::string name);
	Mesh* CreateFuelBar3(std::string name);
	Mesh* CreateSea(std::string name);
	Mesh* CreateMesh(std::string name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
}
