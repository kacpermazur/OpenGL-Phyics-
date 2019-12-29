#include "ResoruceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image/stb_image.h"

std::map<std::string, Shader> ResourceManager::m_Shaders;
std::map<std::string, Texture> ResourceManager::m_Textures;

Shader ResourceManager::LoadShader(const char* vertexShader, const char* fragmentShader,
	std::string name)
{
	m_Shaders[name] = LoadShaderFromFile(vertexShader, fragmentShader);
	return m_Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
	return m_Shaders[name];
}

Texture ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	m_Textures[name] = LoadTextureFromFile(file, alpha);
	return m_Textures[name];
}

Texture& ResourceManager::GetTexture(std::string name)
{
	return m_Textures[name];
}

void ResourceManager::Clear()
{
	for(auto& shader : m_Shaders)
	{
		glDeleteProgram(shader.second.m_BindID);
	}

	for(auto& texture : m_Textures)
	{
		glDeleteTextures(1, &texture.second.m_BindID);
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

Texture ResourceManager::LoadTextureFromFile(const char* file, bool& alpha)
{
	Texture texture;

	if (alpha)
	{
		texture.m_internal_format = GL_RGBA;
		texture.m_image_format = GL_RGBA;
	}

	int width, height, bpp;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* image = stbi_load(file, &width, &height, &bpp, 4);

	texture.Generate(width, height, bpp, image);

	if(image)
		stbi_image_free(image);

	return texture;
}
