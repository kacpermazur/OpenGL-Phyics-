#include "GameObject.h"

GameObject::GameObject()
	: m_position(0,0,0), m_size(1,1,1), m_rot(0.0f), m_color(1.0f), m_texture(), m_isSolid(false)
{
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture& texture, glm::vec3 rot, glm::vec3 color)
	: m_position(pos), m_size(size), m_rot(rot), m_color(color), m_texture(texture), m_isSolid(false)

{
}

GameObject::~GameObject()
{
}

void GameObject::Draw(Renderer& renderer)
{
	renderer.Draw(this->m_texture, this->m_position, this->m_size, this->m_rotation, this->m_rot, this->m_color);
}
