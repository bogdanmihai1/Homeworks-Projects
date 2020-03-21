#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#include "CameraTema.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		void RenderSeaMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat4 modelMatrix;
		bool gameOver;
		bool collision;
		bool firstPerson;
		bool c1, c2, c3, c4, c5;
		bool accelerate;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		float currFuel;
		float planeRotation;
		float going_up;
		float tCloud;
		float tCloud2;
		float plane_position;
		float deltaY;
		float last_mouse_move;
		float my_planeY;
		float plane_angle;
		float obsX;
		float obsY;
		float fuelPos;
		float delta_fy;
		float fuelAngle1;
		float fuelAngle2;
		float fuelAngle3;
		float fuelAngle4;
		float fuelAngle5;
		float fx1, fx2, fx3, fx4, fx5;
		float fy1, fy2, fy3, fy4, fy5;
		int lifes;
		int score;
		int difficulty;
		int cloud1Y;
		int cloud2Y;
		glm::mat4 projectionMatrix;
		CameraTema2::Camera2* camera;
};
