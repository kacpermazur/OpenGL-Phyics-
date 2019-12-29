#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResoruceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

#include <iostream>

//todo: Add Entities Transfrom & Collider

// AABB Collisions
bool OnEnterTrigger2D(GameObject& target, GameObject& other)
{
	bool onCollisonX = target.m_position.x + target.m_size.x >= other.m_position.x && other.m_position.x + other.m_size.x >= target.m_position.x;
	
	bool onCollisonY = target.m_position.y + target.m_size.y >= other.m_position.y && other.m_position.y + other.m_size.y >= target.m_position.y;

	return onCollisonX && onCollisonY;
}

// App State Data
SpriteRenderer* renderer;
GameObject* player;
GameObject* testObj;

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
	ResourceManager::LoadTexture("res/img/pepe.png", GL_TRUE, "pepe");

	// Renderer ToDO: Renderer Class Agnostic (2D/3D) 
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	player = new GameObject(glm::vec3(300, 300,0),glm::vec3(100, 100,1), ResourceManager::GetTexture("sonic"));
	testObj = new GameObject(glm::vec3(100, 100, 0), glm::vec3(100, 100, 1), ResourceManager::GetTexture("pepe"));
}

void Application::InputHandler(float& delta)
{
	if(this->m_state == ACTIVE)
	{
		// ToDo: InputManager Class
		
		float movementSpeed = 200.0f * delta;

		if(this->m_input[GLFW_KEY_W])
		{
			player->m_position.y -= movementSpeed;
		}
		if (this->m_input[GLFW_KEY_S])
		{
			player->m_position.y += movementSpeed;
		}
		if (this->m_input[GLFW_KEY_D])
		{
			player->m_position.x += movementSpeed;
		}
		if (this->m_input[GLFW_KEY_A])
		{
			player->m_position.x -= movementSpeed;
		}
		
	}
}

void Application::Update(float& delta)
{
	this->PhysicsUpdate();
}

void Application::PhysicsUpdate()
{
	if(OnEnterTrigger2D(*player, *testObj))
	{
		std::cout << "2D collison has occured!" << std::endl;
	}
}

void Application::Render()
{
	
	player->Draw(*renderer);
	testObj->Draw(*renderer);
}
