#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class SpriteRenderer
{
private:
	Shader m_shader;
	unsigned int m_quadVAO;
	void InitializeRenderData();

public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

	void DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(5, 5), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

