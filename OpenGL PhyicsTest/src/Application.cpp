#include "Application.h"

#include "ResoruceManager.h"
#include "SpriteRenderer.h"

#include <iostream>

SpriteRenderer* renderer;

Application::Application(const unsigned width, const unsigned height)
	: m_width(width), m_height(height), m_input(), m_state(ACTIVE)
{
}

Application::~Application()
{
	delete renderer;
}

void Application::Initialize()
{
	ResourceManager::LoadShader("res/shaders/Sprite.vs", "res/shaders/Sprite.frag", "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_width), static_cast<float>(this->m_height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Bind().SetUniform1i("u_image", 0);
	ResourceManager::GetShader("sprite").Bind().SetUniformMat4f("u_projection", projection);

	ResourceManager::LoadTexture("res/img/redsonic.png", GL_TRUE, "sonic");

	auto testShader = ResourceManager::GetShader("sprite");
	renderer = new SpriteRenderer(testShader);
}

void Application::InputHandler(float& delta)
{
	
}

void Application::Update(float& delta)
{
}

void Application::Render()
{
	auto testTexture = ResourceManager::GetTexture("sonic");
	
	renderer->DrawSprite(testTexture, glm::vec2(200, 200), glm::vec2(200, 200), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
