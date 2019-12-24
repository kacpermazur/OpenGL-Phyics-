#pragma once
#include <map>
#include <string>

#include "Shader.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> m_Shaders;

	static Shader LoadShader(const char* vertexShader, const char* fragmentShader, std::string name);
	static Shader GetShader(std::string name);

	static void Clear();
	
private:
	ResourceManager() {}
	static Shader LoadShaderFromFile(const char* vertexShader, const char* fragmentShader);
	
};

