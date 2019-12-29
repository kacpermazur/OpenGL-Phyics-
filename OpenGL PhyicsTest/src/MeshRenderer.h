#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"
#include "ModelLoader.h"
#include "VertexLayout.h"


class MeshRenderer
{
private:
	Shader m_Shader;
	unsigned int m_VertexBuffer;
	unsigned int m_VertexArray;
	unsigned int m_IndexBuffer;
	unsigned int m_Count;
	void InitializeRenderData(Mesh& mesh, const VertexLayout& layout);

public:
	MeshRenderer(Mesh& mesh, const VertexLayout& layout, Shader& shader);
	~MeshRenderer();

	void DrawMesh(Texture& texture, glm::vec3 position, glm::vec3 size = glm::vec3(5, 5, 5), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

