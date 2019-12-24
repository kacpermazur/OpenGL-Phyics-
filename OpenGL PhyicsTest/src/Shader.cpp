#include "Shader.h"

Shader::Shader()
{
}

Shader& Shader::Bind()
{
	glUseProgram(this->m_BindID);
	return *this;
}

void Shader::Compile(const std::string* vertexShader, const std::string* fragmentShader)
{
}

void Shader::SetUniform4f(const std::string* name, float v0, float v1, float v2, float v3, bool useShader)
{
}

void Shader::SetUniform4f(const std::string* name, glm::vec3 vec, bool useShader)
{
}

void Shader::SetUniform1i(const std::string* name, int v0, bool useShader)
{
}

void Shader::SetUniformMat4f(const std::string* name, const glm::mat4& matrix, bool useShader)
{
}

void Shader::ShaderErrorCheck(unsigned& id, std::string type)
{
}
