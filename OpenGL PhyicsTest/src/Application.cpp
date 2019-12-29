#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	// Renderer ToDO: Renderer Class Agnostic (2D/3D) 
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	player = new GameObject(glm::vec3(200, 200,0),glm::vec3(200, 200,1), ResourceManager::GetTexture("sonic"));
}

void Application::InputHandler(float& delta)
{
	if(this->m_state == ACTIVE)
	{
		// ToDo: InputManager Class
		
		float movementSpeed = 200.0f * delta;

		if(this->m_input[GLFW_KEY_W])
		{
			player->m_position.y += movementSpeed;
		}
		if (this->m_input[GLFW_KEY_S])
		{
			player->m_position.y -= movementSpeed;
		}
		if (this->m_input[GLFW_KEY_D])
		{
			player->m_position.y += movementSpeed;
		}
		if (this->m_input[GLFW_KEY_A])
		{

		}
		
	}
}

void Application::Update(float& delta)
{
	this->PhysicsUpdate();
}

void Application::PhysicsUpdate()
{
	
}

void Application::Render()
{
	
	player->Draw(*renderer);
}

//todo: Add Entities Transfrom & Collider

// AABB Collisions
static bool OnEnterTrigger2D(GameObject& target, GameObject& other)
{
	return true;
}