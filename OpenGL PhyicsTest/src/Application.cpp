#include "Application.h"

#include "ResoruceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

#include <iostream>

// App State Data
SpriteRenderer* renderer;
GameObject* player;

Application::Application(const unsigned width, const unsigned height)
	: m_width(width), m_height(height), m_input(), m_state(ACTIVE)
{
}

Application::~Application()
{
	delete renderer;
	delete player;
}

void Application::Initialize()
{
	// Shader Loading
	ResourceManager::LoadShader("res/shaders/Sprite.vs", "res/shaders/Sprite.frag", "sprite");

	// Perspective Setup
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_width), static_cast<float>(this->m_height), 0.0f, -1.0f, 1.0f);

	// Uniform Binds
	ResourceManager::GetShader("sprite").Bind().SetUniform1i("u_image", 0);
	ResourceManager::GetShader("sprite").Bind().SetUniformMat4f("u_projection", projection);

	// Texture loading
	ResourceManager::LoadTexture("res/img/redsonic.png", GL_TRUE, "sonic");

	// Renderer
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	player = new GameObject(glm::vec3(200, 200,0),glm::vec3(200, 200,1), ResourceManager::GetTexture("sonic"));
}

void Application::InputHandler(float& delta)
{
	
}

void Application::Update(float& delta)
{
}

void Application::Render()
{
	
	player->Draw(*renderer);
}
