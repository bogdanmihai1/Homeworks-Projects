#include "Objects.h"

#include <Core/Engine.h>
#include <math.h>
#define PI 3.14


Mesh* Objects::CreateSquare(std::string name, short diff)
{
	std::vector<VertexFormat> vertices;
	if (diff == 0) {
		// obstacol simplu
		glm::vec3 color1 = glm::vec3(1, 0, 0);
		glm::vec3 color2 = glm::vec3(0.2f, 0, 0);
		vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color1));
		vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(1, 2, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(0, 2, 0), color1));
	} else if (diff == 1) {
		// obstacol simplu
		glm::vec3 color1 = glm::vec3(0, 1, 0);
		glm::vec3 color2 = glm::vec3(0, 0.2f, 0);
		vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color1));
		vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(1, 2, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(0, 2, 0), color1));
	}
	else if (diff == 2) {
		// obstacol simplu
		glm::vec3 color1 = glm::vec3(0, 0, 1);
		glm::vec3 color2 = glm::vec3(0, 0, 0.2f);
		vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color1));
		vertices.push_back(VertexFormat(glm::vec3(1, 0, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(1, 2, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(0, 2, 0), color1));
	}
	else {
		// obstacol oblic
		glm::vec3 color1 = glm::vec3(1, 0.52f, 0.77f);
		glm::vec3 color2 = glm::vec3(0.9f, 0.32f, 0.5f);
		vertices.push_back(VertexFormat(glm::vec3(2, 0, 0), color1));
		vertices.push_back(VertexFormat(glm::vec3(3, 0, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(1, 2, 0), color2));
		vertices.push_back(VertexFormat(glm::vec3(0, 2, 0), color1));
	}

	Mesh* obs = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											3, 0, 2 };
	
	obs->InitFromData(vertices, indices);
	return obs;
}

Mesh* Objects::CreateBird(std::string name, glm::vec3 color, glm::vec3 wing_color, short flying)
{
	std::vector<VertexFormat> vertices = {
		// corpul
		VertexFormat(glm::vec3(0, 0.25f,  0), color),
		VertexFormat(glm::vec3(0.5f, 0,  0), color),
		VertexFormat(glm::vec3(1.5f, 0,  0), color),
		VertexFormat(glm::vec3(2, 0.25f,  0), color),
		// aripile
		VertexFormat(glm::vec3(0.5f, 1,  0), wing_color),
		VertexFormat(glm::vec3(1.5f, 1,  0), wing_color)
	};
	if (!flying) {
		// aripa in sus
		vertices.push_back(VertexFormat(glm::vec3(1, 1.25f, 0), wing_color));
	}
	else {
		// aripa in jos
		vertices.push_back(VertexFormat(glm::vec3(1, 0.5f, 0.001f), wing_color));
	}

	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6
	};

	// capul
	float centerx = 2.5f; 
	float centery = 0.5f;
	vertices.push_back(VertexFormat(glm::vec3(centerx, centery, 0), wing_color)); // centrul capului

	for (int i = 1; i <= 100; i++) {
		float theta = (2 * PI) * i / 100;
		float outerx = sin(theta);
		float outery = cos(theta);

		vertices.push_back(VertexFormat(glm::vec3(centerx + 0.5*outerx, centery + 0.5*outery, 0), wing_color));
	}

	for (int i = 8; i < 107; i++) {
		indices.push_back(7);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(7);
	indices.push_back(107);
	indices.push_back(8);

	// ochiul
	glm::vec3 black = glm::vec3(0, 0, 0);
	vertices.push_back(VertexFormat(glm::vec3(2.66f, 0.55f, 0.01f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.66f, 0.75f, 0.01f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.80f, 0.55f, 0.01f), black));
	indices.push_back(109);
	indices.push_back(110);
	indices.push_back(108);

	// ciocul
	glm::vec3 peakColor = glm::vec3(1, 0, 0);
	vertices.push_back(VertexFormat(glm::vec3(3.5f, 0.5f, 0.01f), peakColor));
	indices.push_back(111);
	indices.push_back(40);
	indices.push_back(20);

	// restul corpului(am schimbat forma din patrat in octagon si am adaugat la final restul puncte;pr)
	vertices.push_back(VertexFormat(glm::vec3(2, 0.75f, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(1.5f, 1, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 1, 0), color));
	vertices.push_back(VertexFormat(glm::vec3(0, 0.75f, 0), color));

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(112);

	for (int i = 112; i <= 114; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	// creasta
	glm::vec3 colorH = glm::vec3(0, 0, 1);
	vertices.push_back(VertexFormat(glm::vec3(1.9f, 1.1f, -0.1f), colorH));
	vertices.push_back(VertexFormat(glm::vec3(2.65f, 1.1f, -0.1f), colorH));
	vertices.push_back(VertexFormat(glm::vec3(2.1f, 0.9f, -0.1f), colorH));
	vertices.push_back(VertexFormat(glm::vec3(2.85f, 0.9f, -0.1f), colorH));

	indices.push_back(116);
	indices.push_back(118);
	indices.push_back(119);

	indices.push_back(117);
	indices.push_back(116);
	indices.push_back(119);

	// coada
	glm::vec3 tail = glm::vec3(0, 0, 1);
	vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.66f, 0), tail));

	indices.push_back(120);
	indices.push_back(0);
	indices.push_back(115);

	black = glm::vec3(0, 0, 0);
	// picior
	vertices.push_back(VertexFormat(glm::vec3(0.6, 0.25f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.62f, 0.25f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.9f, -0.2f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.92f, -0.2f, -0.1f), black));

	indices.push_back(121);
	indices.push_back(122);
	indices.push_back(123);

	indices.push_back(121);
	indices.push_back(123);
	indices.push_back(124);

	vertices.push_back(VertexFormat(glm::vec3(0.91f, -0.16f, 0), black));
	vertices.push_back(VertexFormat(glm::vec3(0.90f, -0.3f, 0), black));
	vertices.push_back(VertexFormat(glm::vec3(1.07f, -0.3f, 0), black));

	indices.push_back(125);
	indices.push_back(126);
	indices.push_back(127);
	

	Mesh* bird = new Mesh(name);
	bird->InitFromData(vertices, indices);
	return bird;
}

Mesh* Objects::CreateCloud(std::string name)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	glm::vec3 white = glm::vec3(1, 1, 1);

	vertices.push_back(VertexFormat(glm::vec3(2, 0, -5), white));  // primul centru
	vertices.push_back(VertexFormat(glm::vec3(6, 0, -5), white));  // al doilea centru
	
	float px, py, pi = 3.14, angle;
	float r1 = 2, r2 = 1;
	for (int i = 0; i <= 50; i++) {
		angle = pi * i / 50;
		px = r1 * cos(angle);
		py = r2 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(2 + px, py, -5), white));
	}

	for (int i = 2; i < 52; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	for (int i = 0; i <= 50; i++) {
		angle = pi * i / 50;
		px = r1 * cos(angle);
		py = r2 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(6 + px, py, -5), white));
	}

	for (int i = 54; i < 104; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}


	Mesh* cloud = new Mesh(name);
	cloud->InitFromData(vertices, indices);
	return cloud;
}

Mesh* Objects::CreateGround(std::string name)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	glm::vec3 green = glm::vec3(0.04f, 0.4f, 0.13f);

	vertices.push_back(VertexFormat(glm::vec3(2, 0, -5), green));  // primul centru
	vertices.push_back(VertexFormat(glm::vec3(6, 0, -5), green));  // al doilea centru

	float px, py, pi = 3.14, angle;
	float r1 = 2, r2 = 1;
	for (int i = 0; i <= 50; i++) {
		angle = pi * i / 50;
		px = r1 * cos(angle);
		py = r2 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(2 + px, py, -5), green));
	}

	for (int i = 2; i < 52; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	for (int i = 0; i <= 50; i++) {
		angle = pi * i / 50;
		px = r1 * cos(angle);
		py = r2 * sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(6 + px, py, -5), green));
	}

	for (int i = 54; i < 104; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}


	Mesh* cloud = new Mesh(name);
	cloud->InitFromData(vertices, indices);
	return cloud;
}

Mesh* Objects::CreateStars(std::string name)
{
	std::vector<VertexFormat> vertices;
	glm::vec3 star = glm::vec3(1, 0.8f, 0.43f);

	vertices.push_back(VertexFormat(glm::vec3(0, 0.8f, -5), star)); // stanga
	vertices.push_back(VertexFormat(glm::vec3(0.2f, 0, -5), star));  // picior stanga
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.2f, -5), star));  // mijloc jos
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 1.2f, -5), star));  // mijloc sus
	vertices.push_back(VertexFormat(glm::vec3(0.8f, 0, -5), star));  // picior dreapta
	vertices.push_back(VertexFormat(glm::vec3(1, 0.8f, -5), star)); // dreapta


	std::vector<unsigned short> indices = {
		1, 3, 2,
		2, 3, 4,
		0, 5, 2
	};
	

	Mesh* stars = new Mesh(name);
	stars->InitFromData(vertices, indices);
	return stars;
}

Mesh* Objects::CreateSun(std::string name)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	glm::vec3 sun = glm::vec3(0.98f, 0.83f, 0.25f);
	glm::vec3 sun_center = glm::vec3(1, 0.6f, 0);

	vertices.push_back(VertexFormat(glm::vec3(0, 0, -6), sun_center));  // centru

	float px, py, pi = 3.14, angle;
	for (int i = 0; i <= 100; i++) {
		angle = 2 * pi * i / 100;
		px = cos(angle);
		py = sin(angle);
		vertices.push_back(VertexFormat(glm::vec3(px, py, -6), sun));
	}

	for (int i = 1; i <= 100; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	Mesh* mySun = new Mesh(name);
	mySun->InitFromData(vertices, indices);
	return mySun;
}