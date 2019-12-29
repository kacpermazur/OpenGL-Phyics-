#include "MeshRenderer.h"


void MeshRenderer::InitializeRenderData(Mesh& mesh, const VertexLayout& layout)
{
	// Vertex Array
	glGenVertexArrays(1, &m_VertexArray);

	const std::vector<VertexElement>& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto e = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.elementCount, e.dataType, e.isNormalized, layout.GetStride(), (const void*)offset);
		offset = e.elementCount * VertexElement::TypeSize(e.dataType);
	}
	
	// Vertex Buffer
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

	// IndexBuffer
	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	m_Count = mesh.indices.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);
	
}

MeshRenderer::MeshRenderer(Mesh& mesh, const VertexLayout& layout, Shader& shader)
{
	this->InitializeRenderData(mesh,layout);
}

MeshRenderer::~MeshRenderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &m_IndexBuffer);
}

void MeshRenderer::DrawMesh(Texture& texture, glm::vec3 position, glm::vec3 size, float rotation, glm::vec3 color)
{
	this->m_Shader.Bind();

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.5f* size.z));

	model = glm::scale(model, size);

	this->m_Shader.SetUniformMat4f("u_model", model);
	this->m_Shader.SetUniform3f("u_spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, nullptr);
	
}
