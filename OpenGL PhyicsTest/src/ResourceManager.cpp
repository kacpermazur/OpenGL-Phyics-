#include "ResoruceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ResourceManager::m_Shaders;

Shader ResourceManager::LoadShader(const char* vertexShader, const char* fragmentShader,
	std::string name)
{
	m_Shaders[name] = LoadShaderFromFile(vertexShader, fragmentShader);
	return m_Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return m_Shaders[name];
}

void ResourceManager::Clear()
{
	for(auto& shader : m_Shaders)
	{
		glDeleteProgram(shader.second.m_BindID);
	}
}


Shader ResourceManager::LoadShaderFromFile(const char* vertexShader, const char* fragmentShader)
{
	std::string vertexShaderCode, fragmentShaderCode;

	try
	{
		std::ifstream vShaderFile(vertexShader);
		std::ifstream fShaderFile(fragmentShader);
		std::stringstream vStream, fStream;

		vStream << vShaderFile.rdbuf();
		fStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		
		vertexShaderCode = vStream.str();
		fragmentShaderCode = fStream.str();
		
	}
	catch (std::exception& e)
	{
		std::cout << "Unable to read Shaders!" << std::endl;
	}

	const char* vShaderCode = vertexShaderCode.c_str();
	const char* fShaderCode = fragmentShaderCode.c_str();

	Shader newShader;
	newShader.Compile(vShaderCode, fShaderCode);
	return newShader;
}