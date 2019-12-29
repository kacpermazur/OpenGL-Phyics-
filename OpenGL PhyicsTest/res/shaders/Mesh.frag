#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_image;
uniform vec3 u_spriteColor;

void main()
{
	color = vec4(u_spriteColor, 1.0) * texture(u_image, TexCoords);
};