#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <iostream>

#include "Application.h"
#include "ResoruceManager.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Application PhysicsCollisonsApp(SCREEN_WIDTH, SCREEN_HEIGHT);S

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics OpenGL", NULL, NULL);
	if (!window)
	{void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
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
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	PhysicsCollisonsApp.Initialize();

	std::cout << glGetString(GL_VERSION) << std::endl;


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	PhysicsCollisonsApp.m_state = ACTIVE;

	glm::vec3 testValue(0.0f, 0.0f, 0.0f);

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSetKeyCallback(window, key_callback);

		PhysicsCollisonsApp.InputHandler(deltaTime);
		PhysicsCollisonsApp.Update(deltaTime);

		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplGlfwGL3_NewFrame();
		
		PhysicsCollisonsApp.Render();

		{
			ImGui::SliderFloat3("Rotation", &testValue.x, -1.0f, 2.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	ResourceManager::Clear();
	
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "Escape Pressed" << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		std::cout << "1 is pressed" << std::endl;
	}
	
	if(key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			PhysicsCollisonsApp.m_input[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			PhysicsCollisonsApp.m_input[key] = GL_FALSE;
	}
}