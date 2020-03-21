#include "Tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <Core/Engine.h>
#include "Transforms.h"
#include "Objects.h"
#include "CameraTema.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	srand(time(NULL));

	// scena va avea dimensiunile (1000, 600)
	camera = new CameraTema::Camera();
	camera->Set(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::ortho(0.0f, 1000.0f, 0.0f, 600.0f, 0.01f, 400.0f);

	// initializari variabile folosite in joc
	going_up = 0;
	score = -150;
	difficulty = 1;
	obs_shape = 0;
	obs_scale = 0;
	going_up = 0;
	obs_color = 1;
	translateX = 0;
	translateY = 0;
	tCloud = 0;
	scaleX = 1;
	scaleY = 1;
	dist = 100 + rand() % 60;
	dim_jos = 20 + rand() % 80;
	dim_sus = 300 - dist - dim_jos;
	angularStep = 0;

	// cele doua pasari: una cu aripa in sus, alta cu aripa in jos
	Mesh* bird = Objects::CreateBird("bird", glm::vec3(0.5f, 0.5f, 0), glm::vec3(0.835f, 0.5f, 0), 0);
	AddMeshToList(bird);
	Mesh* bird_down = Objects::CreateBird("bird_down", glm::vec3(0.5f, 0.5f, 0), glm::vec3(0.835f, 0.5f, 0), 1);
	AddMeshToList(bird_down);

	// obstacol basic
	Mesh* obs_up = Objects::CreateSquare("obs_up", 0);
	AddMeshToList(obs_up);
	Mesh* obs_down = Objects::CreateSquare("obs_down", 0);
	AddMeshToList(obs_down);
	
	// obstacol basic, alta culoare
	Mesh* obs_up_2 = Objects::CreateSquare("obs_up_2", 1);
	AddMeshToList(obs_up_2);
	Mesh* obs_down_2 = Objects::CreateSquare("obs_down_2", 1);
	AddMeshToList(obs_down_2);

	// obstacol basic, culoarea 3
	Mesh* obs_up_3 = Objects::CreateSquare("obs_up_3", 2);
	AddMeshToList(obs_up_3);
	Mesh* obs_down_3 = Objects::CreateSquare("obs_down_3", 2);
	AddMeshToList(obs_down_3);

	// obstacol oblic
	Mesh* obs1_up = Objects::CreateSquare("obs1_up", 3);
	AddMeshToList(obs1_up);
	Mesh* obs1_down = Objects::CreateSquare("obs1_down", 3);
	AddMeshToList(obs1_down);

	// decor
	Mesh* cloud = Objects::CreateCloud("cloud");
	AddMeshToList(cloud);
	Mesh* field = Objects::CreateGround("field");
	AddMeshToList(field);
	Mesh* star = Objects::CreateStars("star");
	AddMeshToList(star);
	Mesh* sun = Objects::CreateSun("sun");
	AddMeshToList(sun);
}

void Tema1::FrameStart()
{
	// dupa o anumita dificultate se va face noapte
	if (night == false) {
		glClearColor(0.529f, 0.807f, 0.921f, 1);
	}
	else {
		glClearColor(0.15f, 0.15f, 0.15f, 1);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	anim += 3 * deltaTimeSeconds;
	tCloud += 4 * deltaTimeSeconds;
	// going_up va fi 1 cand se va apasa SPACEBAR
	// va descreste continuu si va decide miscarea
	// pasarii pe OY (sus sau jos)
	going_up -= deltaTimeSeconds;

	// variabile pentru animatia pasarii
	// translatia pe OY si rotatia pentru urcare/cadere
	if (going_up > 0) {
		translateY += 2 * deltaTimeSeconds;
		angularStep = 3.14 / 8;
	}
	else {
		translateY -= 2 * deltaTimeSeconds;
		angularStep = -(3.14 / 8);
	}

	// pozitia ciocului pe axa OY
	// low -> pasarea este in cadere
	// high -> pasarea este in urcare
	low  = 300 + 50 * translateY - 10;
	high = 380 + 50 * translateY + 10;

	// daca pasarea a iesit din scena
	if (low < 0 || high > 600)
	{
		cout << "Final score:" << score/10 << '\n';
		exit(0);
	}

	// decor
	// primul nor
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transforms::Translate3D(850 - tCloud, 500);
	modelMatrix *= Transforms::Scale3D(40, 40);
	RenderMesh(meshes["cloud"], shaders["VertexColor"], modelMatrix);
	// al doilea nor
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transforms::Translate3D(400 - 2 * tCloud, 300);
	modelMatrix *= Transforms::Scale3D(35, 20);
	RenderMesh(meshes["cloud"], shaders["VertexColor"], modelMatrix);
	// solul
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transforms::Translate3D(-50, 0);
	modelMatrix *= Transforms::Scale3D(138, 40);
	RenderMesh(meshes["field"], shaders["VertexColor"], modelMatrix);

	if (night == true) {
		// stele
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(200, 500);
		modelMatrix *= Transforms::Scale3D(40, 40);
		RenderMesh(meshes["star"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(500, 300);
		modelMatrix *= Transforms::Scale3D(40, 40);
		RenderMesh(meshes["star"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(800, 100);
		modelMatrix *= Transforms::Scale3D(40, 40);
		RenderMesh(meshes["star"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(-10, 250);
		modelMatrix *= Transforms::Scale3D(40, 40);
		RenderMesh(meshes["star"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(600, 350);
		modelMatrix *= Transforms::Scale3D(40, 40);
		RenderMesh(meshes["star"], shaders["VertexColor"], modelMatrix);
	}
	else {
		// soarele pentru zi
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(0, 600);
		modelMatrix *= Transforms::Scale3D(120, 120);
		RenderMesh(meshes["sun"], shaders["VertexColor"], modelMatrix);
	}

	// animatia pasarii
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transforms::Translate3D(200, 300 + 50 * translateY);
	modelMatrix *= Transforms::Scale3D(40, 40);
	modelMatrix *= Transforms::RotateOX(angularStep);

	// pentru ca pasarea sa dea din aripi, am creat doua modele
	// variabila anim decide schimbarea dintre cele doua
	if ((int)floor(anim) % 2) {
		RenderMesh(meshes["bird"], shaders["VertexColor"], modelMatrix);
	}
	else {
		RenderMesh(meshes["bird_down"], shaders["VertexColor"], modelMatrix);
	}

	score++;

	if (!(score % 200) && score > 0) {
		// incep de la un scor negativ pentru ca scorul minim pe care il
		// pot obtine sa fie aproximativ 0 (timpul pana cand pasarea ar
		// cadea din scena daca nu s-ar apasa tasta space sau ar lovi un
		// obstacol nu ar trebui sa fie adaugat la scor)

		// afisez scorul si cresc dificultatea periodic, in functie de scor
		difficulty++;
		if (difficulty >= 10) {
			night = true;
		}
		cout << "Score:" << score/10 << '\n';
	}

	translateX += difficulty * deltaTimeSeconds * 50;

	// mereu cand un obstacol dispare
	if (translateX > 1200) {
		translateX = 0;

		// sansa de 25% ca obstacolele sa fie animate
		if (rand() % 4 == 1) {
			move_obs = 15;
			obs_up = -1;
			obs_scale = 0;
		}
		else {
			move_obs = 0;
			obs_up = 0;
			obs_scale = 0;
		}

		// culoarea obstacolelor
		switch (rand() % 3) {
			case 0: obs_color = 0; break;
			case 1: obs_color = 1; break;
			case 2: obs_color = 2; break;
			default: obs_color = 2;
		}

		// dimensiunile obstacolelor pentru ca pasarea sa poata trece
		dist = 100 + rand() % 60;
		dim_jos = 20 + rand() % 80;
		dim_sus = 300 - dist - dim_jos;

		// dupa o anumita dificultate pot aparea obstacole noi
		if (difficulty > 10 && rand() % 4 == 1) {
			obs_shape = 1;
		}
		else {
			obs_shape = 0;
		}
	}

	// animatia obstacolelor prin scalare
	if (obs_up == -1 && obs_scale < move_obs) {
		obs_scale += 20*deltaTimeSeconds;
	}
	else if (obs_up == -1 && obs_scale > move_obs) {
		obs_up = 1;
	}
	if (obs_up == 1 && obs_scale > 0) {
		obs_scale -= 20*deltaTimeSeconds;
	}
	else if (obs_up == 1 && obs_scale <= 0) {
		obs_up = -1;
	}

	if (obs_shape == 0) {
		// verific coliziuni
		if (1000 - translateX <= 340 && 1000 - translateX >= 200) {
			// if OX overlap, check for OY overlaps
			if (going_up > 0) {
				// forma pasarii imi permite sa verific coliziunile in functie
				// de pozitia varfului ciocului
				if (high >= 600 - 2 * (dim_sus + obs_scale)) {
					cout << "Final score:" << score / 10 << '\n';
					exit(0);
				}
				if (high <= 2 * (dim_jos + obs_scale)) {
					cout << "Final score:" << score / 10 << '\n';
					exit(0);
				}
			}
			else {
				if (low >= 600 - 2 * (dim_sus + obs_scale)) {
					cout << "Final score:" << score / 10 << '\n';
					exit(0);
				}
				if (low <= 2 * (dim_jos + obs_scale)) {
					cout << "Final score:" << score / 10 << '\n';
					exit(0);
				}
			}
		}

		// obstacol de jos
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1000 - translateX, 0);
		modelMatrix *= Transforms::Scale3D(80, dim_jos + obs_scale);
		if (obs_color == 0) {
			RenderMesh(meshes["obs_up"], shaders["VertexColor"], modelMatrix);
		} else if (obs_color == 1) {
			RenderMesh(meshes["obs_up_2"], shaders["VertexColor"], modelMatrix);
		} else {
			RenderMesh(meshes["obs_up_3"], shaders["VertexColor"], modelMatrix);
		}

		// obstacol de sus
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1000 - translateX, 600);
		modelMatrix *= Transforms::Scale3D(80, -dim_sus - obs_scale);
		if (obs_color == 0) {
			RenderMesh(meshes["obs_down"], shaders["VertexColor"], modelMatrix);
		} else if (obs_color == 1) {
			RenderMesh(meshes["obs_down_2"], shaders["VertexColor"], modelMatrix);
		} else {
			RenderMesh(meshes["obs_down_3"], shaders["VertexColor"], modelMatrix);
		}
	} else {
		if (1080 - translateX <= 340 && 1080 - translateX >= 200) {
			// daca pasarea nu trece initial prin locul liber, aceasta nu va
			// mai putea trece dupa
			if (going_up > 0) {
				// forma pasarii imi permite sa verific coliziunile in functie
				// de pozitia varfului ciocului
				if (high >= 600 - 2 * (dim_sus + obs_scale)) {
					gameOverUp = true;
				} else if (high <= 2 * (dim_jos + obs_scale)) {
					gameOverDown = true;
				}
			}
			else {
				if (low >= 600 - 2 * (dim_sus + obs_scale)) {
					gameOverUp = true;
				} else if (low <= 2 * (dim_jos + obs_scale)) {
					gameOverDown = true;
				}
			}
		}

		// daca nu a reusit sa treaca, astept coliziunea cu obstacolul
		if (gameOverUp == true) {
			if (low <= 1080 - translateX || high <= 1080 - translateX) {
				cout << "Final score:" << score / 10 << '\n';
				exit(0);
			}
		}
		if (gameOverDown == true) {
			if (low >= 1080 - translateX || high >= 1080 - translateX) {
				cout << "Final score:" << score / 10 << '\n';
				exit(0);
			}
		}

		// obstacol de jos
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1080 - translateX, 0);
		modelMatrix *= Transforms::Scale3D(80, dim_jos + obs_scale);
		RenderMesh(meshes["obs1_up"], shaders["VertexColor"], modelMatrix);

		// obstacol de sus
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transforms::Translate3D(1080 - translateX, 600);
		modelMatrix *= Transforms::Scale3D(80, -dim_sus - obs_scale);
		RenderMesh(meshes["obs1_down"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
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

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// pasarea zboara in sus
	if (key == GLFW_KEY_SPACE) {
		going_up = 1;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
