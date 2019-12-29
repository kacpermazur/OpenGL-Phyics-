#pragma once
#include <map>
#include <string>

#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> m_Shaders;
	static std::map<std::string, Texture> m_Textures;

	static Shader LoadShader(const char* vertexShader, const char* fragmentShader, std::string name);
	static Shader& GetShader(std::string name);

	static Texture LoadTexture(const char* file, bool alpha, std::string name);
	static Texture& GetTexture(std::string name);

	static void Clear();
	
private:
	ResourceManager() {}
	
	static Shader LoadShaderFromFile(const char* vertexShader, const char* fragmentShader);
	static Texture LoadTextureFromFile(const char* file, bool& alpha);
	
};

