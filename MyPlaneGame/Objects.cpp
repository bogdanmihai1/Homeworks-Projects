#include "Objects.h"

#include <Core/Engine.h>
#include <math.h>
#define PI 3.14


Mesh* Objects::PlaneBody(std::string name)
{
	std::vector<VertexFormat> vertices;
	glm::vec3 lightRed = glm::vec3(0, 0, 1);
	glm::vec3 darkRed = glm::vec3(0, 0, 0.5f);
	glm::vec3 blue = glm::vec3(0, 0, 1);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 brown = glm::vec3(0.54f, 0.27f, 0.07f);
	glm::vec3 skin = glm::vec3(1, 0.89f, 0.76f);
	glm::vec3 black = glm::vec3(0, 0, 0);
	// corpul avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, 0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, -0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}

	// indicii corpului
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	// aripile
	{
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, -2.2f), darkRed));
	}
	// indici aripi
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());

	// fata avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, -0.70f), white));
	}
	// indicii fetei
	std::vector<unsigned short> ind3;
	for (std::vector<unsigned short>::iterator it = ind2.begin(); it != ind2.end(); ++it) {
		ind3.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind3.begin(), ind3.end());

	// coada
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, -0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, -0.1f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind4;
	for (std::vector<unsigned short>::iterator it = ind3.begin(); it != ind3.end(); ++it) {
		ind4.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind4.begin(), ind4.end());


	// corp pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.4f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 0.4f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 1.3f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 1.3f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.4f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 0.4f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 1.3f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 1.3f, -0.4f), brown));
	}
	// indicii
	std::vector<unsigned short> ind5;
	for (std::vector<unsigned short>::iterator it = ind4.begin(); it != ind4.end(); ++it) {
		ind5.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind5.begin(), ind5.end());

	// cap pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.3f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.3f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.6f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.6f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.3f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.3f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.6f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.6f, -0.22f), skin));
	}
	// indicii
	std::vector<unsigned short> ind6;
	for (std::vector<unsigned short>::iterator it = ind5.begin(); it != ind5.end(); ++it) {
		ind6.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind6.begin(), ind6.end());

	// corp avion v2.0
	{
		vertices.push_back(VertexFormat(glm::vec3(0, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(0, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, -0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind7;
	for (std::vector<unsigned short>::iterator it = ind6.begin(); it != ind6.end(); ++it) {
		ind7.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind7.begin(), ind7.end());

	// ochelari pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.45f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.45f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.55f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.55f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.45f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.45f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.55f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.55f, -0.27f), brown));
	}
	// indicii
	std::vector<unsigned short> ind8;
	for (std::vector<unsigned short>::iterator it = ind7.begin(); it != ind7.end(); ++it) {
		ind8.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind8.begin(), ind8.end());
	
	// roata spate
	// suport
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, -0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, -0.2f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind9;
	for (std::vector<unsigned short>::iterator it = ind8.begin(); it != ind8.end(); ++it) {
		ind9.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind9.begin(), ind9.end());
	// roata
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, -0.15f), brown));
	}
	// indicii
	std::vector<unsigned short> ind10;
	for (std::vector<unsigned short>::iterator it = ind9.begin(); it != ind9.end(); ++it) {
		ind10.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind10.begin(), ind10.end());

	// roti fata
	// roata dreapta
	{
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.4f), brown));
	}
	// indicii
	std::vector<unsigned short> ind11;
	for (std::vector<unsigned short>::iterator it = ind10.begin(); it != ind10.end(); ++it) {
		ind11.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind11.begin(), ind11.end());

	// roata stanga
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.4f), brown));
	// indicii
	std::vector<unsigned short> ind12;
	for (std::vector<unsigned short>::iterator it = ind11.begin(); it != ind11.end(); ++it) {
		ind12.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind12.begin(), ind12.end());
	// roata dreapta - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.35f), black));
	// indicii
	std::vector<unsigned short> ind13;
	for (std::vector<unsigned short>::iterator it = ind12.begin(); it != ind12.end(); ++it) {
		ind13.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind13.begin(), ind13.end());

	// roata stanga - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.35f), black));
	// indicii
	std::vector<unsigned short> ind14;
	for (std::vector<unsigned short>::iterator it = ind13.begin(); it != ind13.end(); ++it) {
		ind14.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind14.begin(), ind14.end());

	// coada- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2   , 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2   , 1   , 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1   , 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2   , 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2   , 1   , -1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1   , -1), darkRed));
	// indicii
	std::vector<unsigned short> ind15;
	for (std::vector<unsigned short>::iterator it = ind14.begin(); it != ind14.end(); ++it) {
		ind15.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind15.begin(), ind15.end());

	// coada2- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1, 1), darkRed));
	// indicii
	std::vector<unsigned short> ind16;
	for (std::vector<unsigned short>::iterator it = ind15.begin(); it != ind15.end(); ++it) {
		ind16.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind16.begin(), ind16.end());

	// par static pilot
	vertices.push_back(VertexFormat(glm::vec3(0.54, 1.33, 0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.8, 1.33, 0.2), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.54, 1.63, 0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.8, 1.63, 0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.54, 1.33, -0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.8, 1.33, -0.2), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.54, 1.63, -0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.8, 1.63, -0.23), brown));
	// indicii
	std::vector<unsigned short> ind17;
	for (std::vector<unsigned short>::iterator it = ind16.begin(); it != ind16.end(); ++it) {
		ind17.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind17.begin(), ind17.end());

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::PlanePropeller(std::string name) {
	glm::vec3 black = glm::vec3(0, 0, 0);
	glm::vec3 white = glm::vec3(1, 1, 1);
	
	// legatura dintre elice si avion
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.1f, 0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5, -0.1f, 0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.1f, 0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5, 0.1f, 0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.1f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5, -0.1f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.1f, -0.1f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5, 0.1f, -0.1f), black));

	// indicii
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};
	// elice verticala
	vertices.push_back(VertexFormat(glm::vec3(2.5f, -1, 0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, -1, 0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, 1, 0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, 1, 0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, -1, -0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, -1, -0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, 1, -0.3f), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, 1, -0.3f), black));
	// indici
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());
	// elice orizontala
	vertices.push_back(VertexFormat(glm::vec3(2.5f, -0.3f, 1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, -0.3f, 1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, 0.3f, 1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, 0.3f, 1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, -0.3f, -1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, -0.3f, -1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.5f, 0.3f, -1), black));
	vertices.push_back(VertexFormat(glm::vec3(2.6f, 0.3f, -1), black));
	// indici
	std::vector<unsigned short> ind3;
	for (std::vector<unsigned short>::iterator it = ind2.begin(); it != ind2.end(); ++it) {
		ind3.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind3.begin(), ind3.end());



	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateCloud(std::string name)
{
	glm::vec3 white = glm::vec3(0.82, 0.82, 0.82);
	glm::vec3 white2 = glm::vec3(1, 1, 1);

	// primul cub
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, -7), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, -7), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, -7), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, -7), white2));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};
	// al doilea cub
	vertices.push_back(VertexFormat(glm::vec3(5, -1, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(7, -1, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(5, 1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(7, 1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(5, -1, -7), white2));
	vertices.push_back(VertexFormat(glm::vec3(7, -1, -7), white2));
	vertices.push_back(VertexFormat(glm::vec3(5, 1, -7), white));
	vertices.push_back(VertexFormat(glm::vec3(7, 1, -7), white));
	// indici
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::PilotHair(std::string name)
{
	glm::vec3 brown = glm::vec3(0.54f, 0.27f, 0.07f);
	glm::vec3 brown2 = glm::vec3(0.69f, 0.13f, 0.13f);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.24, 1.44, -0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.56, 1.44, -0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.24, 1.6, -0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.56, 1.6, -0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.24, 1.44, 0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.56, 1.44, 0.23), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.24, 1.6, 0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.56, 1.6, 0.23), brown));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	vertices.push_back(VertexFormat(glm::vec3(0.04, 1.45, -0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 1.45, -0.23), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.04, 1.55, -0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 1.55, -0.23), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.04, 1.45, 0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 1.45, 0.23), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.04, 1.55, 0.17), brown2));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 1.55, 0.23), brown2));
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateSmoke(std::string name)
{
	glm::vec3 white = glm::vec3(0.41, 0.41, 0.41);
	glm::vec3 white2 = glm::vec3(0.5, 0.5, 0.5);

	// primul cub
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, -1), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, -1), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, -1), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, -1), white2));
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, 1), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, 1), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, 1), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, 1), white2));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateWhiteBox(std::string name)
{
	glm::vec3 white = glm::vec3(0.82, 0.82, 0.82);
	glm::vec3 white2 = glm::vec3(1, 1, 1);

	// primul cub
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, -5), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1.5f, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1.5f, -5), white2));
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, -7), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, -7), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1.5f, -7), white2));
	vertices.push_back(VertexFormat(glm::vec3(1, 1.5f, -7), white2));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
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

Mesh* Objects::CreateObstacle(std::string name)
{
	std::vector<VertexFormat> vertices;
	glm::vec3 lightRed = glm::vec3(0.6f, 0, 0);
	glm::vec3 darkRed = glm::vec3(1, 0, 0);
	glm::vec3 blue = glm::vec3(0, 0, 1);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 brown = glm::vec3(0.54f, 0.27f, 0.07f);
	glm::vec3 skin = glm::vec3(1, 0.89f, 0.76f);
	glm::vec3 black = glm::vec3(0, 0, 0);
	// corpul avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, 0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, -0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}

	// indicii corpului
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	// aripile
	{
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, -2.2f), darkRed));
	}
	// indici aripi
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());

	// fata avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, -0.70f), white));
	}
	// indicii fetei
	std::vector<unsigned short> ind3;
	for (std::vector<unsigned short>::iterator it = ind2.begin(); it != ind2.end(); ++it) {
		ind3.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind3.begin(), ind3.end());

	// coada
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, -0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, -0.1f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind4;
	for (std::vector<unsigned short>::iterator it = ind3.begin(); it != ind3.end(); ++it) {
		ind4.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind4.begin(), ind4.end());


	// corp pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.4f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 0.4f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 1.3f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 1.3f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.4f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 0.4f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.5f, 1.3f, -0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1, 1.3f, -0.4f), brown));
	}
	// indicii
	std::vector<unsigned short> ind5;
	for (std::vector<unsigned short>::iterator it = ind4.begin(); it != ind4.end(); ++it) {
		ind5.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind5.begin(), ind5.end());

	// cap pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.3f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.3f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.6f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.6f, 0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.3f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.3f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.55f, 1.6f, -0.22f), skin));
		vertices.push_back(VertexFormat(glm::vec3(0.85f, 1.6f, -0.22f), skin));
	}
	// indicii
	std::vector<unsigned short> ind6;
	for (std::vector<unsigned short>::iterator it = ind5.begin(); it != ind5.end(); ++it) {
		ind6.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind6.begin(), ind6.end());

	// corp avion v2.0
	{
		vertices.push_back(VertexFormat(glm::vec3(0, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(0, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, -0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind7;
	for (std::vector<unsigned short>::iterator it = ind6.begin(); it != ind6.end(); ++it) {
		ind7.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind7.begin(), ind7.end());

	// ochelari pilot
	{
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.45f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.45f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.55f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.55f, 0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.45f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.45f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.75f, 1.55f, -0.27f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.95f, 1.55f, -0.27f), brown));
	}
	// indicii
	std::vector<unsigned short> ind8;
	for (std::vector<unsigned short>::iterator it = ind7.begin(); it != ind7.end(); ++it) {
		ind8.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind8.begin(), ind8.end());

	// roata spate
	// suport
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, -0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, -0.2f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind9;
	for (std::vector<unsigned short>::iterator it = ind8.begin(); it != ind8.end(); ++it) {
		ind9.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind9.begin(), ind9.end());
	// roata
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, -0.15f), brown));
	}
	// indicii
	std::vector<unsigned short> ind10;
	for (std::vector<unsigned short>::iterator it = ind9.begin(); it != ind9.end(); ++it) {
		ind10.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind10.begin(), ind10.end());

	// roti fata
	// roata dreapta
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.4f), brown));
	// indicii
	std::vector<unsigned short> ind11;
	for (std::vector<unsigned short>::iterator it = ind10.begin(); it != ind10.end(); ++it) {
		ind11.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind11.begin(), ind11.end());

	// roata stanga
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.4f), brown));
	// indicii
	std::vector<unsigned short> ind12;
	for (std::vector<unsigned short>::iterator it = ind11.begin(); it != ind11.end(); ++it) {
		ind12.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind12.begin(), ind12.end());
	// roata dreapta - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.35f), black));
	// indicii
	std::vector<unsigned short> ind13;
	for (std::vector<unsigned short>::iterator it = ind12.begin(); it != ind12.end(); ++it) {
		ind13.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind13.begin(), ind13.end());

	// roata stanga - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.35f), black));
	// indicii
	std::vector<unsigned short> ind14;
	for (std::vector<unsigned short>::iterator it = ind13.begin(); it != ind13.end(); ++it) {
		ind14.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind14.begin(), ind14.end());

	// coada- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, -1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1, -1), darkRed));
	// indicii
	std::vector<unsigned short> ind15;
	for (std::vector<unsigned short>::iterator it = ind14.begin(); it != ind14.end(); ++it) {
		ind15.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind15.begin(), ind15.end());

	// coada2- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1, 1), darkRed));
	// indicii
	std::vector<unsigned short> ind16;
	for (std::vector<unsigned short>::iterator it = ind15.begin(); it != ind15.end(); ++it) {
		ind16.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind16.begin(), ind16.end());

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateLives(std::string name) {
	std::vector<VertexFormat> vertices;
	glm::vec3 lightRed = glm::vec3(0, 0, 1);
	glm::vec3 darkRed = glm::vec3(0, 0, 0.5f);
	glm::vec3 blue = glm::vec3(0, 0, 1);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 brown = glm::vec3(0.54f, 0.27f, 0.07f);
	glm::vec3 skin = glm::vec3(1, 0.89f, 0.76f);
	glm::vec3 black = glm::vec3(0, 0, 0);
	// corpul avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, 0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 0, -0.35f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.35f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}

	// indicii corpului
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
	};

	// aripile
	{
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, 2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, 2.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.71f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-0.8f, 0.81f, -2.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(1.3f, 0.81f, -2.2f), darkRed));
	}
	// indici aripi
	std::vector<unsigned short> ind2;
	for (std::vector<unsigned short>::iterator it = indices.begin(); it != indices.end(); ++it) {
		ind2.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind2.begin(), ind2.end());

	// fata avionului
	{
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, 0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, -0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2, 0.95f, -0.70f), white));
		vertices.push_back(VertexFormat(glm::vec3(2.4f, 0.95f, -0.70f), white));
	}
	// indicii fetei
	std::vector<unsigned short> ind3;
	for (std::vector<unsigned short>::iterator it = ind2.begin(); it != ind2.end(); ++it) {
		ind3.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind3.begin(), ind3.end());

	// coada
	{
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, 0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, -0.3f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-2, 1.4f, -0.1f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.3f, 1.4f, -0.1f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind4;
	for (std::vector<unsigned short>::iterator it = ind3.begin(); it != ind3.end(); ++it) {
		ind4.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind4.begin(), ind4.end());

	// corp avion v2.0
	{
		vertices.push_back(VertexFormat(glm::vec3(0, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, 0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, 0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(0, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(2, -1, -0.75f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, -0.75f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(2, 1, -0.75f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind7;
	for (std::vector<unsigned short>::iterator it = ind4.begin(); it != ind4.end(); ++it) {
		ind7.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind7.begin(), ind7.end());

	// roata spate
	// suport
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, 0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, 0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, -0.7f, -0.2f), lightRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.7f, 1, -0.2f), darkRed));
		vertices.push_back(VertexFormat(glm::vec3(-1.6f, 1, -0.2f), darkRed));
	}
	// indicii
	std::vector<unsigned short> ind9;
	for (std::vector<unsigned short>::iterator it = ind7.begin(); it != ind7.end(); ++it) {
		ind9.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind9.begin(), ind9.end());
	// roata
	{
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, 0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.8f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.8f, -0.5f, -0.15f), brown));
		vertices.push_back(VertexFormat(glm::vec3(-1.5f, -0.5f, -0.15f), brown));
	}
	// indicii
	std::vector<unsigned short> ind10;
	for (std::vector<unsigned short>::iterator it = ind9.begin(); it != ind9.end(); ++it) {
		ind10.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind10.begin(), ind10.end());

	// roti fata
	// roata dreapta
	{
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.6f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, 0.4f), brown));
		vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, 0.4f), brown));
	}
	// indicii
	std::vector<unsigned short> ind11;
	for (std::vector<unsigned short>::iterator it = ind10.begin(); it != ind10.end(); ++it) {
		ind11.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind11.begin(), ind11.end());

	// roata stanga
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.6f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1.5f, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(0.3f, -1, -0.4f), brown));
	vertices.push_back(VertexFormat(glm::vec3(1.7f, -1, -0.4f), brown));
	// indicii
	std::vector<unsigned short> ind12;
	for (std::vector<unsigned short>::iterator it = ind11.begin(); it != ind11.end(); ++it) {
		ind12.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind12.begin(), ind12.end());
	// roata dreapta - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, 0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, 0.35f), black));
	// indicii
	std::vector<unsigned short> ind13;
	for (std::vector<unsigned short>::iterator it = ind12.begin(); it != ind12.end(); ++it) {
		ind13.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind13.begin(), ind13.end());

	// roata stanga - details
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.65f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1.35f, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(0.6f, -1, -0.35f), black));
	vertices.push_back(VertexFormat(glm::vec3(1.4f, -1, -0.35f), black));
	// indicii
	std::vector<unsigned short> ind14;
	for (std::vector<unsigned short>::iterator it = ind13.begin(); it != ind13.end(); ++it) {
		ind14.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind14.begin(), ind14.end());

	// coada- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, -1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, -1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1, -1), darkRed));
	// indicii
	std::vector<unsigned short> ind15;
	for (std::vector<unsigned short>::iterator it = ind14.begin(); it != ind14.end(); ++it) {
		ind15.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind15.begin(), ind15.end());

	// coada2- orizontal
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 0.7f, 0), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.1f, 1, 0), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 0.7f, 1), lightRed));
	vertices.push_back(VertexFormat(glm::vec3(-2, 1, 1), darkRed));
	vertices.push_back(VertexFormat(glm::vec3(-1.4f, 1, 1), darkRed));
	// indicii
	std::vector<unsigned short> ind16;
	for (std::vector<unsigned short>::iterator it = ind15.begin(); it != ind15.end(); ++it) {
		ind16.push_back(*it + 8);
	}

	indices.insert(indices.end(), ind16.begin(), ind16.end());

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateFuel(std::string name) {
	glm::vec3 color1 = glm::vec3(0.25f, 0.87f, 0.81f);
	glm::vec3 color2 = glm::vec3(0, 0.8, 0.81f);

	// primul cub
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0, 2, 0), color1));
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 1), color2));
	vertices.push_back(VertexFormat(glm::vec3(-1, 0, -1), color2));
	vertices.push_back(VertexFormat(glm::vec3(1, 0, -1), color2));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		1, 3, 0,
		0, 2, 3
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateFuelBar1(std::string name) {
	glm::vec3 black = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, 5), black));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, 5), black));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, 5), black));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, 5), black));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateFuelBar2(std::string name) {
	glm::vec3 white = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-1, -1, 6), white));
	vertices.push_back(VertexFormat(glm::vec3(1, -1, 6), white));
	vertices.push_back(VertexFormat(glm::vec3(-1, 1, 6), white));
	vertices.push_back(VertexFormat(glm::vec3(1, 1, 6), white));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateFuelBar3(std::string name) {
	glm::vec3 white = glm::vec3(0.25f, 0.87f, 0.81f);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 7), white));
	vertices.push_back(VertexFormat(glm::vec3(2, 0, 7), white));
	vertices.push_back(VertexFormat(glm::vec3(0, 2, 7), white));
	vertices.push_back(VertexFormat(glm::vec3(2, 2, 7), white));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2
	};

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateSea(std::string name) {
	glm::vec3 blue = glm::vec3(0, 0, 0.6f);
	glm::vec3 blue2 = glm::vec3(0, 0, 1);
	std::vector<VertexFormat> vertices;
	// fata primului cilindru
	vertices.push_back(VertexFormat(glm::vec3(0, 0, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0, 0.85, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.3, 0.75, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(1, 0.2, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.9, -0.3, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.2, -0.95, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.6, -0.7, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-1, -0.1, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.8, 0.4, -5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.4, 0.6, -5), blue));

	// fata celui de-al doilea cilindru
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0, 0.85, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.3, 0.75, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(1, 0.2, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.9, -0.3, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(0.2, -0.95, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.6, -0.7, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-1, -0.1, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.8, 0.4, 5), blue));
	vertices.push_back(VertexFormat(glm::vec3(-0.4, 0.6, 5), blue));

	// puncte interioare
	vertices.push_back(VertexFormat(glm::vec3(0.15, 1, 2), blue2));
	vertices.push_back(VertexFormat(glm::vec3(0.7, 0.85, -3), blue2));
	vertices.push_back(VertexFormat(glm::vec3(0.92, -0.35, 4), blue2));
	vertices.push_back(VertexFormat(glm::vec3(0.4, -1, 2.5), blue2));
	vertices.push_back(VertexFormat(glm::vec3(-0.1, -0.6, -1), blue2));
	vertices.push_back(VertexFormat(glm::vec3(-0.7, 0, 0), blue2));
	vertices.push_back(VertexFormat(glm::vec3(-0.85, 0.6, -4), blue2));
	vertices.push_back(VertexFormat(glm::vec3(-0.5, 0.7, 3.3), blue2));
	vertices.push_back(VertexFormat(glm::vec3(-0.1, 0.3, 1.6), blue2));

	// indicii
	std::vector<unsigned short> indices;
	for (int i = 1; i < 9; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);

		indices.push_back(10);
		indices.push_back(i + 10);
		indices.push_back(i + 11);
	}

	indices.push_back(0);
	indices.push_back(9);
	indices.push_back(1);

	indices.push_back(10);
	indices.push_back(19);
	indices.push_back(11);

	for (int i = 1; i < 9; i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 19);

		indices.push_back(i);
		indices.push_back(i + 10);
		indices.push_back(i + 19);

		indices.push_back(i + 1);
		indices.push_back(i + 11);
		indices.push_back(i + 19);

		indices.push_back(i + 10);
		indices.push_back(i + 11);
		indices.push_back(i + 19);
	}


	indices.push_back(9);
	indices.push_back(1);
	indices.push_back(28);

	indices.push_back(9);
	indices.push_back(19);
	indices.push_back(28);

	indices.push_back(19);
	indices.push_back(11);
	indices.push_back(28);

	indices.push_back(1);
	indices.push_back(11);
	indices.push_back(28);

	Mesh* obs = CreateMesh(name, vertices, indices);
	return obs;
}

Mesh* Objects::CreateMesh(std::string name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	glBindVertexArray(0);
	CheckOpenGLError();

	Mesh* object = new Mesh(name);
	object->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	object->vertices = vertices;
	object->indices = indices;
	return object;
}