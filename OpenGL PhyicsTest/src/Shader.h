#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include "glm/mat4x2.hpp"


class Shader
{
private:
	unsigned int m_BindID;

public:
	Shader();
	Shader& Bind();
	

	void Compile(const std::string* vertexShader, const std::string* fragmentShader);

	void SetUniform4f(const std::string* name, float v0, float v1, float v2, float v3, bool useShader = false);
	void SetUniform4f(const std::string* name, glm::vec3 vec, bool useShader = false);
	void SetUniform1i(const std::string* name, int v0, bool useShader = false);
	void SetUniformMat4f(const std::string* name, const glm::mat4& matrix, bool useShader = false);

private:
	unsigned int ShaderErrorCheck(unsigned int& id, unsigned int& type);
	unsigned int CompileShaderID(unsigned int type, const std::string* source);
};