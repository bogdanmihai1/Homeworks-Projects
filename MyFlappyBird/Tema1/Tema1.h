#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#include "CameraTema.h"

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
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
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		float anim;
		float going_up;
		float tCloud;
		int score;
		float low;   // y min for bird
		float high;  // y max for bird
		int difficulty;
		int scale_down;
		int scale_up;
		int dist;
		int dim_jos;
		int dim_sus;
		int obs_shape;
		int move_obs;  // cat se micsoreaza obstacolele
		int obs_up;  // daca se inchid, deschid sau raman asa obstacolele
		float obs_scale;
		short obs_color;
		short scaleChange = 1;
		bool gameOverUp = false;    // pentru obstacol oblic
		bool gameOverDown = false;  // pentru obstacol oblic
		bool night = false;
		glm::mat4 projectionMatrix;
		CameraTema::Camera* camera;
};
