#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_text;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

out vec3 frag_color;

void main()
{
	frag_color = v_color;
	float dx = cos(time)/10 + 1;
	float dy = sin(time)/10 + 1;

	gl_Position = Projection * View * Model * vec4(v_position.x * dx, v_position.y * dy, v_position.z, 1.0);
}
