#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class Renderer
{
private:
	Shader m_shader;
	unsigned int m_quadVAO;
	void InitializeRenderData();

public:
	Renderer(Shader& shader);
	~Renderer();

	void DrawSprite(Texture& texture, glm::vec3 position, glm::vec3 size = glm::vec3(5, 5,5), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

