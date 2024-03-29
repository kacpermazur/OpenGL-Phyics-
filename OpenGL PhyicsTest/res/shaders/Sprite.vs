#version 330 core
layout (location = 0) in vec4 vertex;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    TexCoords = texCoord;
    gl_Position = u_projection * u_view * u_model * vec4(vertex.xyz, 1.0);
}