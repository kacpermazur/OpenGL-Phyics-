#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Renderer.h"

class GameObject
{
public:
	glm::vec3 m_position, m_size;
	glm::vec3 m_rot;
	glm::vec3 m_color;
	
	float m_rotation;
	bool m_isSolid;
	
	Texture m_texture;

	GameObject();
	GameObject(glm::vec3 pos, glm::vec3 size, Texture& texture, glm::vec3 m_rot = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f));
	virtual ~GameObject();
	virtual void Draw(Renderer& renderer);
};
