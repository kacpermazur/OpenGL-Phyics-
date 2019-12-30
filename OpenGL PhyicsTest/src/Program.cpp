#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Application.h"
#include "ResoruceManager.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Application PhysicsCollisonsApp(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		std::cout << "Error: GLEW didnt initilize" << std::endl;
	
	glGetError();

	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	PhysicsCollisonsApp.Initialize();

	std::cout << glGetString(GL_VERSION) << std::endl;


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	PhysicsCollisonsApp.m_state = ACTIVE;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//glfwSetKeyCallback(window, key_callback);

		PhysicsCollisonsApp.InputHandler(deltaTime);
		
		PhysicsCollisonsApp.Update(deltaTime);

		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		PhysicsCollisonsApp.Render();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		
	}


	ResourceManager::Clear();
	
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if(key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			PhysicsCollisonsApp.m_input[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			PhysicsCollisonsApp.m_input[key] = GL_FALSE;
	}
}