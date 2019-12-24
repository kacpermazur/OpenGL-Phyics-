#include "Shader.h"
#include <iostream>

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
	unsigned int vertexID, fragmentID;

	vertexID = CompileShaderID(GL_VERTEX_SHADER, vertexShader);
	fragmentID = CompileShaderID(GL_FRAGMENT_SHADER, fragmentShader);
	
	this->m_BindID = glCreateProgram();
	
	glAttachShader(this->m_BindID, vertexID);
	glAttachShader(this->m_BindID, fragmentID);

	glLinkProgram(this->m_BindID);
	glValidateProgram(this->m_BindID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3, bool useShader)
{
	if (useShader)
		this->Bind();

	glUniform4f(glGetUniformLocation(this->m_BindID, name), v0, v1, v2, v3);
}

void Shader::SetUniform4f(const char* name, glm::vec4 vec, bool useShader)
{
	if (useShader)
		this->Bind();

	glUniform4f(glGetUniformLocation(this->m_BindID, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniform1i(const char* name, int v0, bool useShader)
{
	if (useShader)
		this->Bind();

	glUniform1i(glGetUniformLocation(this->m_BindID, name), v0);
}

void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader)
		this->Bind();
	
	glUniformMatrix4fv(glGetUniformLocation(this->m_BindID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::ShaderErrorCheck(unsigned int& id, unsigned int& type)
{
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader Compiler Error: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CompileShaderID(unsigned type, const std::string* source)
{
	unsigned int id = glCreateShader(type);

	const char* src = source->c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	
	return ShaderErrorCheck(id, type);
}
