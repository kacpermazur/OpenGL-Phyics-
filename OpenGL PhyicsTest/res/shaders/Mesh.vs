#version 330 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 normal;

out vec2 v_TexCoord;

uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
	v_TexCoord = texCoord;
	gl_Position = u_projection * u_model * vertex;
};