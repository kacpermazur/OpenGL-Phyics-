#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "glm/mat4x2.hpp"


class Shader
{
public:
	unsigned int m_BindID;
	
	Shader();
	Shader& Bind();
	
	void Compile(const char* vertexShader, const char* fragmentShader);

	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3, bool useShader = false);
	void SetUniform4f(const char* name, glm::vec4 vec, bool useShader = false);
	void SetUniform1i(const char* name, int v0, bool useShader = false);
	void SetUniformMat4f(const char* name, const glm::mat4& matrix, bool useShader = false);

private:
	unsigned int ShaderErrorCheck(unsigned int& id, unsigned int& type);
	unsigned int CompileShaderID(unsigned int type, const char* source);
};