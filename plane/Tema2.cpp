#include "Tema2.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <Core/Engine.h>
#include "Transforms.h"
#include "Objects.h"
#include "CameraTema.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	srand(time(NULL));

	// scena va avea dimensiunile (1000, 600)
	camera = new CameraTema2::Camera2();
	camera->Set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::ortho(0.0f, 1000.0f, 0.0f, 600.0f, 0.01f, 1000.0f);

	// initializari variabile folosite in joc
	{
		lifes = 3;
		gameOver = false;
		collision = false;
		firstPerson = false;
		c1 = false;
		c2 = false;
		c3 = false;
		c4 = false;
		c5 = false;
		accelerate = false;
		going_up = 0;
		currFuel = 96;
		score = 0;
		delta_fy = 0;
		difficulty = 1;
		translateX = 0;
		translateY = 0;
		tCloud = 0;
		tCloud2 = 0;
		cloud1Y = 100;
		cloud2Y = 50;
		obsX = 0;
		fuelPos = 1250;
		obsY = 0;
		scaleX = 1;
		scaleY = 1;
		angularStep = 0;
		planeRotation = 0;
		deltaY = 0;
		plane_angle = 0;
		last_mouse_move = 200;
	}

	// meshes
	{
		Mesh* plane = Objects::PlaneBody("plane");
		AddMeshToList(plane);
		Mesh* propeller = Objects::PlanePropeller("propeller");
		AddMeshToList(propeller);
		Mesh* hair = Objects::PilotHair("hair");
		AddMeshToList(hair);
		Mesh* smoke = Objects::CreateSmoke("smoke");
		AddMeshToList(smoke);
		Mesh* cloud = Objects::CreateCloud("cloud");
		AddMeshToList(cloud);
		Mesh* middleCloud = Objects::CreateWhiteBox("middleCloud");
		AddMeshToList(middleCloud);
		Mesh* field = Objects::CreateGround("field");
		AddMeshToList(field);
		Mesh* fuelBar1 = Objects::CreateFuelBar1("fuelBar1");
		AddMeshToList(fuelBar1);
		Mesh* fuelBar2 = Objects::CreateFuelBar2("fuelBar2");
		AddMeshToList(fuelBar2);
		Mesh* fuelBar3 = Objects::CreateFuelBar3("fuelBar3");
		AddMeshToList(fuelBar3);
		Mesh* life = Objects::CreateLives("life");
		AddMeshToList(life);
		Mesh* obstacle = Objects::CreateObstacle("obstacle");
		AddMeshToList(obstacle);
		Mesh* fuel = Objects::CreateFuel("fuel");
		AddMeshToList(fuel);
		Mesh* sea = Objects::CreateSea("sea");
		AddMeshToList(sea);
	}

	// shader
	{
		Shader* shader = new Shader("ShaderTema");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{
	glClearColor(0.529f, 0.807f, 0.921f, 1);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (firstPerson == true) {
		camera->SetFirstPerson(glm::vec3(350, deltaY, -500), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
	}

	if (accelerate == true && gameOver == false) {
		deltaTimeSeconds *= 2;
		currFuel -= deltaTimeSeconds;
	}

	tCloud += 300 * deltaTimeSeconds;
	tCloud2 += 450 * deltaTimeSeconds;
	obsX += (400 + 30*difficulty) * deltaTimeSeconds;
	angularStep += 10 * deltaTimeSeconds;
	planeRotation += deltaTimeSeconds;
	translateX += difficulty * deltaTimeSeconds * 50;

	// miscarea avionului pe OY
	if (gameOver == false) {
		deltaY += (going_up) * 300 * deltaTimeSeconds;
		plane_position = 400 + deltaY;
		my_planeY = 600 - plane_position;
		if (last_mouse_move - my_planeY > -10 && last_mouse_move - my_planeY < 10) {
			going_up = 0;
		}
		else if (last_mouse_move - my_planeY < -10) {
			going_up = 1;
		}
		else {
			going_up = -1;
		}

		score++;
		currFuel = fmax(currFuel - 3 * deltaTimeSeconds, 0);

		if (!(score % 100)) {
			// afisez scorul si cresc dificultatea periodic, in functie de scor
			difficulty++;
			cout << "Score: " << score / 10 << '\n';
		}
	}
	else {
		going_up = -1;
		deltaY -= 250 * deltaTimeSeconds;
		if (deltaY < -600) {
			cout << "Final score: " << score / 10 << '\n';
			exit(0);
		}
	}
	
	if (going_up == 1) {
		plane_angle = fmin(plane_angle + 2*deltaTimeSeconds, 0.78);
	}
	else if (going_up == -1) {
		plane_angle = fmax(plane_angle - 2*deltaTimeSeconds, -0.78);
	}
	else {
		if (plane_angle > 0) {
			plane_angle = fmax(plane_angle - 2*deltaTimeSeconds, 0);
		} else if (plane_angle < 0) {
			plane_angle = fmin(plane_angle + 2*deltaTimeSeconds, 0);
		}
	}

	// interfata
	{
		if (firstPerson == false) {
			// contur combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(850, 550, 0);
			modelMatrix *= Transforms::Scale3D(100, 20, 1);
			RenderMesh(meshes["fuelBar1"], shaders["VertexColor"], modelMatrix);

			// combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(850, 550, 0);
			modelMatrix *= Transforms::Scale3D(96, 15, 1);
			RenderMesh(meshes["fuelBar2"], shaders["VertexColor"], modelMatrix);

			// combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(754, 535, 0);
			modelMatrix *= Transforms::Scale3D(currFuel, 15, 1);
			RenderMesh(meshes["fuelBar3"], shaders["VertexColor"], modelMatrix);

			if (currFuel == 0 || lifes == 0) {
				gameOver = true;
			}

			// vieti
			if (lifes > 0) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(50, 550, 0);
				modelMatrix *= Transforms::Scale3D(10, 10, 1);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
			if (lifes > 1) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(125, 550, 0);
				modelMatrix *= Transforms::Scale3D(10, 10, 1);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
			if (lifes > 2) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(200, 550, 0);
				modelMatrix *= Transforms::Scale3D(10, 10, 1);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
		}
		else {
			// contur combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(850, 550 + deltaY, 350);
			modelMatrix *= Transforms::Scale3D(1, 20, 100);
			modelMatrix *= Transforms::RotateOY(3.14 / 2);
			RenderMesh(meshes["fuelBar1"], shaders["VertexColor"], modelMatrix);

			// combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(840, 550 + deltaY, 350);
			modelMatrix *= Transforms::Scale3D(1, 15, 96);
			modelMatrix *= Transforms::RotateOY(3.14 / 2);
			RenderMesh(meshes["fuelBar2"], shaders["VertexColor"], modelMatrix);

			// combustibil maxim
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(830, 535 + deltaY, 255);
			modelMatrix *= Transforms::Scale3D(1, 15, -currFuel);
			modelMatrix *= Transforms::RotateOY(3.14 / 2);
			RenderMesh(meshes["fuelBar3"], shaders["VertexColor"], modelMatrix);

			if (currFuel == 0 || lifes == 0) {
				gameOver = true;
			}

			// vieti
			if (lifes > 0) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(800, 550 + deltaY, -450);
				modelMatrix *= Transforms::Scale3D(10, 10, 10);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
			if (lifes > 1) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(800, 550 + deltaY, -400);
				modelMatrix *= Transforms::Scale3D(10, 10, 10);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
			if (lifes > 2) {
				modelMatrix = glm::mat4(1);
				modelMatrix *= Transforms::Translate3D(800, 550 + deltaY, -350);
				modelMatrix *= Transforms::Scale3D(10, 10, 10);
				modelMatrix *= Transforms::RotateOX(planeRotation);
				modelMatrix *= Transforms::RotateOZ(planeRotation);
				RenderMesh(meshes["life"], shaders["VertexColor"], modelMatrix);
				RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
			}
		}
	}

	// obstacole
	{
		if (collision == true) {
			obsY -= 200 * deltaTimeSeconds;
			obsX -= (300 + 25 * difficulty) * deltaTimeSeconds;
		}

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1300 - obsX, 400 + obsY, 0);
		modelMatrix *= Transforms::Scale3D(-15, 15, 15);
		modelMatrix *= Transforms::RotateOY(-0.3f);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		if (collision == true) {
			modelMatrix *= Transforms::RotateOZ(planeRotation + 5 * deltaTimeSeconds);
		}
		RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1300 - obsX, 400 + obsY, 0);
		modelMatrix *= Transforms::Scale3D(-15, 15, 15);
		modelMatrix *= Transforms::RotateOY(-0.3f);
		modelMatrix *= Transforms::RotateOZ(angularStep);
		RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);

		if (obsX > 1400 || obsY < -400) {
			obsX = 0;
			obsY = rand() % 400 - 200;
			collision = false;
		}
	}

	// combustibil
	{
		/* for (int i = 0; i < 1000; i++)
		angle = 2*PI * i/1000
		x = sin(angle)*500 + 500
		y = cos(angle)*(altitudineY) + 100
		*/
		fuelPos--;
		if (fuelPos < 250) {
			fuelPos = 1250;
			c1 = false;
			c2 = false;
			c3 = false;
			c4 = false;
			c5 = false;
			delta_fy = rand() % 200;
		}

		if (c1 == false) {
			fuelAngle1 = 2 * 3.14f * (fuelPos / 1000);
			fx1 = sin(fuelAngle1) * 600 + 500;
			fy1 = cos(fuelAngle1) * 250 + 100 + delta_fy;

			if (fx1 - 15 <= 490 && fx1 + 15 >= 420) {
				if (fy1 <= 400 + deltaY + 20 && fy1 + 30 >= 400 + deltaY - 20 && gameOver == false) {
						c1 = true;
						currFuel += 15;
						currFuel = fmin(currFuel, 96);
				}
			}

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(fx1, fy1, 0);
			modelMatrix *= Transforms::Scale3D(15, 15, 15);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			modelMatrix *= Transforms::RotateOZ(planeRotation);
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}

		if (c2 == false) {
			fuelAngle2 = 2 * 3.14f * ((fuelPos + 20) / 1000);
			fx2 = sin(fuelAngle2) * 600 + 500;
			fy2 = cos(fuelAngle2) * 250 + 100 + delta_fy;

			if (fx2 - 15 <= 490 && fx2 + 15 >= 420) {
				if (fy2 <= 400 + deltaY + 20 && fy2 + 30 >= 400 + deltaY - 20 && gameOver == false) {
					c2 = true;
					currFuel += 15;
					currFuel = fmin(currFuel, 96);
				}
			}

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(fx2, fy2, 0);
			modelMatrix *= Transforms::Scale3D(15, 15, 15);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			modelMatrix *= Transforms::RotateOZ(planeRotation);
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}

		if (c3 == false) {
			fuelAngle3 = 2 * 3.14f * ((fuelPos + 40) / 1000);
			fx3 = sin(fuelAngle3) * 600 + 500;
			fy3 = cos(fuelAngle3) * 250 + 100 + delta_fy;

			if (fx3 - 15 <= 490 && fx3 + 15 >= 420) {
				if (fy3 <= 400 + deltaY + 20 && fy3 + 30 >= 400 + deltaY - 20 && gameOver == false) {
					c3 = true;
					currFuel += 15;
					currFuel = fmin(currFuel, 96);
				}
			}
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(fx3, fy3, 0);
			modelMatrix *= Transforms::Scale3D(15, 15, 15);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			modelMatrix *= Transforms::RotateOZ(planeRotation);
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}
		if (c4 == false) {
			fuelAngle4 = 2 * 3.14f * ((fuelPos + 60) / 1000);
			fx4 = sin(fuelAngle4) * 600 + 500;
			fy4 = cos(fuelAngle4) * 250 + 100 + delta_fy;

			if (fx4 - 15 <= 490 && fx4 + 15 >= 420) {
				if (fy4 <= 400 + deltaY + 20 && fy4 + 30 >= 400 + deltaY - 20 && gameOver == false) {
					c4 = true;
					currFuel += 15;
					currFuel = fmin(currFuel, 96);
				}
			}

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(fx4, fy4, 0);
			modelMatrix *= Transforms::Scale3D(15, 15, 15);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			modelMatrix *= Transforms::RotateOZ(planeRotation);
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}

		if (c5 == false) {
			fuelAngle5 = 2 * 3.14f * ((fuelPos + 80) / 1000);
			fx5 = sin(fuelAngle5) * 600 + 500;
			fy5 = cos(fuelAngle5) * 250 + 100 + delta_fy;

			if (fx5 - 15 <= 490 && fx5 + 15 >= 420) {
				if (fy5 <= 400 + deltaY + 20 && fy5 + 30 >= 400 + deltaY - 20 && gameOver == false) {
					c5 = true;
					currFuel += 15;
					currFuel = fmin(currFuel, 96);
				}
			}

			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(fx5, fy5, 0);
			modelMatrix *= Transforms::Scale3D(15, 15, 15);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			modelMatrix *= Transforms::RotateOZ(planeRotation);
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}
	}

	// decor //

	// primul nor
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(850 - tCloud, 400 + cloud1Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 20, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(3.14f / 16);
		RenderMesh(meshes["cloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(890 - tCloud, 400 + cloud1Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 20, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation * 1.2f);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(-3.14f / 8);
		RenderMesh(meshes["middleCloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(930 - tCloud, 400 + cloud1Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 20, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation / 2);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(3.14f / 8);
		RenderMesh(meshes["middleCloud"], shaders["VertexColor"], modelMatrix);

		if (tCloud > 1000) {
			cloud1Y = rand() % 200;
			tCloud = -500;
		}
	}

	// al doilea nor
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(400 - tCloud2, 250 + cloud2Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 20, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(3.14f / 16);
		RenderMesh(meshes["cloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(440 - tCloud2, 250 + cloud2Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 22, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation * 1.2f);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(-3.14f / 8);
		RenderMesh(meshes["middleCloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(480 - tCloud2, 250 + cloud2Y, 0);
		modelMatrix *= Transforms::Scale3D(20, 22, 20);
		modelMatrix *= Transforms::Translate3D(0, 0, -6);
		modelMatrix *= Transforms::RotateOZ(planeRotation / 2);
		modelMatrix *= Transforms::Translate3D(0, 0, 6);
		modelMatrix *= Transforms::RotateOX(3.14f / 8);
		RenderMesh(meshes["middleCloud"], shaders["VertexColor"], modelMatrix);

		if (tCloud2 > 550) {
			cloud2Y = rand() % 200;
			tCloud2 = -800;
		}
	}

	// marea
	{
		if (firstPerson == false) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(500, -350, 0);
			modelMatrix *= Transforms::Scale3D(800, 450, 1);
			modelMatrix *= Transforms::RotateOY(3.14f / 32);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			RenderSeaMesh(meshes["sea"], shaders["ShaderTema"], modelMatrix);
		}
		else {
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transforms::Translate3D(500, -350, 0);
			modelMatrix *= Transforms::Scale3D(800, 450, 400);
			modelMatrix *= Transforms::RotateOY(3.14f / 32);
			modelMatrix *= Transforms::RotateOX(planeRotation);
			RenderSeaMesh(meshes["sea"], shaders["ShaderTema"], modelMatrix);
		}
	}

	// animatia avionului
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(450, 400 + deltaY, 0);
		modelMatrix *= Transforms::Scale3D(15, 15, 15);
		modelMatrix *= Transforms::RotateOX(plane_angle);
		modelMatrix *= Transforms::RotateOY(-0.3f);
		modelMatrix *= Transforms::RotateOZ(0.3f);
		if (gameOver == true) {
			modelMatrix *= Transforms::RotateOZ(planeRotation);
		}
		RenderMesh(meshes["plane"], shaders["VertexColor"], modelMatrix);
		RenderMesh(meshes["hair"], shaders["ShaderTema"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(450, 400 + deltaY, 0);
		modelMatrix *= Transforms::Scale3D(15, 15, 15);
		modelMatrix *= Transforms::RotateOX(plane_angle);
		modelMatrix *= Transforms::RotateOY(-0.3f);
		modelMatrix *= Transforms::RotateOZ(angularStep);
		RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);
	}

	if (accelerate == true && gameOver == false) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(400, 400 + deltaY, 0);
		modelMatrix *= Transforms::Scale3D(5, 5, 5);
		modelMatrix *= Transforms::RotateOX(planeRotation);
		modelMatrix *= Transforms::RotateOY(planeRotation);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		RenderMesh(meshes["smoke"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(380, 405 + deltaY, 0);
		modelMatrix *= Transforms::Scale3D(5, 5, 5);
		modelMatrix *= Transforms::RotateOX(planeRotation);
		modelMatrix *= Transforms::RotateOY(planeRotation);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		RenderMesh(meshes["smoke"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(360, 395 + deltaY, 0);
		modelMatrix *= Transforms::Scale3D(5, 5, 5);
		modelMatrix *= Transforms::RotateOX(planeRotation);
		modelMatrix *= Transforms::RotateOY(planeRotation);
		modelMatrix *= Transforms::RotateOZ(planeRotation);
		RenderMesh(meshes["smoke"], shaders["VertexColor"], modelMatrix);
	}

	// coliziuni obstacol
	{
		// OX avion = [420, 490]
		// OX obstacol = [1300 - obsX - 40, 1300 - obsX + 30]
		// OY avion = [400 + deltaY - 20, 400 + deltaY + 20], o eroare de +- 5 din cauza rotatiei
		// OY obstacol = [400 + obsY - 15, 400 + obsY + 15]
		if (1300 - obsX - 40 <= 490 && 1300 - obsX + 30 >= 420) {
			if (400 + obsY - 15 <= 400 + deltaY + 20 && 400 + obsY + 15 >= 400 + deltaY - 20) {
				if (collision == false) {
					collision = true;
					lifes--;
				}
			}
		}
	}
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSeaMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	float time = Engine::GetElapsedTime();
	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint location = glGetUniformLocation(shader->GetProgramID(), "time");
	glUniform1f(location, time);

	mesh->Render();
}

void Tema2::FrameEnd()
{
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		accelerate = true;
	}
	if (key == GLFW_KEY_F) {
		firstPerson = !firstPerson;
		if (firstPerson == false) {
			camera->Set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		accelerate = false;
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::ivec2 resolution = window->GetResolution();
	last_mouse_move = (600 * mouseY) / resolution.y;
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
