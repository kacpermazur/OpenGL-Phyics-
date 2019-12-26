#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	glm::vec3 m_position, m_size;
	glm::vec3 m_velocity;
	
	float m_rotation;
	bool m_isSolid;
	
	Texture m_sprite;

	GameObject();
	GameObject(glm::vec3 pos, glm::vec3 size, glm::vec3 color = glm::vec3(1.0f), glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f));

	virtual void Draw(SpriteRenderer& renderer);
};
