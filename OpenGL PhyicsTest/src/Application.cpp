#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ResoruceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "VertexLayout.h"

#include "ModelLoader.h"

//todo: Add Entities Transfrom & Collider

// AABB Collisions
static bool OnEnterTrigger2D(GameObject& target, GameObject& other)
{
	bool onCollisonX = target.m_position.x + target.m_size.x >= other.m_position.x && other.m_position.x + other.m_size.x >= target.m_position.x;
	bool onCollisonY = target.m_position.y + target.m_size.y >= other.m_position.y && other.m_position.y + other.m_size.y >= target.m_position.y;

	return onCollisonX && onCollisonY;
}

static bool OnEnterTrigger3D(GameObject& target, GameObject& other)
{
	bool onCollisonX = target.m_position.x + target.m_size.x >= other.m_position.x && other.m_position.x + other.m_size.x >= target.m_position.x;
	bool onCollisonY = target.m_position.y + target.m_size.y >= other.m_position.y && other.m_position.y + other.m_size.y >= target.m_position.y;
	bool onCollisonZ = target.m_position.z + target.m_size.z >= other.m_position.z && other.m_position.z + other.m_size.z >= target.m_position.z;

	return onCollisonX && onCollisonY && onCollisonZ;
}

static glm::vec3 ColDirection(GameObject& target, GameObject& other)
{
	//todo make these smaller after testing
	
	float targetBotton = target.m_position.y + target.m_size.y;
	float targetRight = target.m_position.x + target.m_size.x;
	float targetFoward = target.m_position.z + target.m_size.z;

	float otherBotton = other.m_position.y + other.m_size.y;
	float otherRight = other.m_position.x + other.m_size.x;
	float otherFoward = other.m_position.z + other.m_size.z;

	// Collisons
	float colBottom = otherBotton - target.m_position.y;
	float colTop = targetBotton - other.m_position.y;

	float colLeft = targetRight - other.m_position.x;
	float colRight = otherRight - target.m_position.x;

	float colBack = targetFoward - other.m_position.z;
	float colFoward = otherFoward - target.m_position.z;

	if (colTop < colBottom && colTop < colLeft && colTop < colRight && colTop < colBack && colTop < colFoward)
	{
		std::cout << "TOP COLLISION!" << std::endl;
		return glm::vec3(0, 1, 0);
	}
	if (colBottom < colTop && colBottom < colLeft && colBottom < colRight && colBottom < colBack && colBottom < colFoward)
	{
		std::cout << "BOTTOM COLLISION!" << std::endl;
		return glm::vec3(0, -1, 0);
	}
	if (colLeft < colRight && colLeft < colBottom && colLeft < colTop && colLeft < colFoward && colLeft < colBack)
	{
		std::cout << "LEFT COLLISION!" << std::endl;
		return glm::vec3(-1, 0, 0);
	}
	if (colRight < colLeft && colRight < colBottom && colRight < colTop && colRight < colFoward && colRight < colBack)
	{
		std::cout << "RIGHT COLLISION!" << std::endl;
		return glm::vec3(1, 0, 0);
	}
	if (colFoward < colBack && colFoward < colLeft && colFoward < colRight && colFoward < colTop && colFoward < colBottom)
	{
		std::cout << "FOWARD COLLISION!" << std::endl;
		return glm::vec3(0, 0, 1);
	}
	if (colBack < colFoward && colBack < colLeft && colBack < colRight && colBack < colTop && colBack < colBottom)
	{
		std::cout << "BACK COLLISION!" << std::endl;
		return glm::vec3(0, 0, -1);
	}

	std::cout << "ERROR COLLISION!" << std::endl;
	return glm::vec3(0, 0, 0);
}


// App State Data
SpriteRenderer* renderer;
GameObject* player;
GameObject* testObj;

// toDo: Move to physicBody entity
bool collisonOccured = false;

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
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->m_width), static_cast<float>(this->m_height), 0.0f, -1.0f, 200.0f);

	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(this->m_width) / static_cast<float>(this->m_height), 0.1f, 100.0f);

	// Uniform Binds
	ResourceManager::GetShader("sprite").Bind().SetUniform1i("u_image", 0);
	ResourceManager::GetShader("sprite").Bind().SetUniformMat4f("u_projection", projection);

	// Camera
	glm::mat4 view = glm::mat4(1);
	std::cout << glm::to_string(view) << std::endl;
	view = glm::translate(view, glm::vec3(1, 1, 1));
	std::cout << glm::to_string(view) << std::endl;
	
	ResourceManager::GetShader("sprite").Bind().SetUniformMat4f("u_view", view);

	// Texture loading
	ResourceManager::LoadTexture("res/img/redsonic.png", GL_TRUE, "sonic");
	ResourceManager::LoadTexture("res/models/Creeper/Texture.png", GL_TRUE, "pepe");

	// Renderer ToDO: Renderer Class Agnostic (2D/3D) 
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Game Objects
	player = new GameObject(glm::vec3(600, 300,0),glm::vec3(100, 100,100), ResourceManager::GetTexture("pepe"));
	testObj = new GameObject(glm::vec3(200, 300, 0), glm::vec3(100, 100, 100), ResourceManager::GetTexture("pepe"), glm::vec3(0),glm::vec3(1.0f,0.1f,0.1f));

	player->m_rotation = 0.0f;
	testObj->m_rotation = 0.0f;
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
	if(OnEnterTrigger3D(*player, *testObj))
	{
		collisonOccured = true;

		auto test = ColDirection(*player, *testObj);
		
		player->m_position += test * 20.0f;
		testObj->m_position -= test * 20.0f;
	}
	else
	{
		collisonOccured = false;
	}
	
}

void Application::Render()
{
	player->Draw(*renderer);
	testObj->Draw(*renderer);
}
