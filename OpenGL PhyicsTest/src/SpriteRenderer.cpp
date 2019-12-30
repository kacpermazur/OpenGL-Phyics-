#include "SpriteRenderer.h"
#include "VertexLayout.h"

unsigned int test;
unsigned int m_Count;

void SpriteRenderer::InitializeRenderData()
{
	unsigned int VBO;
	unsigned int IBO;

	float vertices[]
	{
		//0.0f, 1.0f, 0.0f, 1.0f, // 0
		//1.0f, 0.0f, 1.0f, 0.0f, // 1
		//0.0f, 0.0f, 0.0f, 0.0f, // 2
		//1.0f, 1.0f, 1.0f, 1.0f, // 3
		//
		0.500000, -0.500000, -0.500000,0.340409, -0.000303,
		0.500000, -0.500000, 0.500000,0.593540, -0.000303,
		-0.500000, -0.500000, 0.500000,0.593540, 0.249793,
		-0.500000, -0.500000, -0.500000,0.340409, 0.249793,
		-0.500000, 0.500000, -0.500000,0.085962, 0.504830,
		-0.500000, 0.500000, 0.500000,0.341672, 0.504830,
		0.500000, 0.500000, 0.500000,0.341672, 0.752417,
		0.500000, 0.500000, -0.500000,0.085962, 0.752417,
		0.500000, -0.500000, -0.500000,0.341137, 0.249562,
		-0.500000, -0.500000, -0.500000,0.593337, 0.249562,
		-0.500000, 0.500000, -0.500000,0.593337, 0.499562,
		0.500000, 0.500000, -0.500000,0.341137, 0.499562,
		-0.500000, 0.500000, 0.500000,0.848302, 0.753039,
		-0.500000, 0.500000, -0.500000,0.595141, 0.753039,
		-0.500000, -0.500000, -0.500000,0.595141, 0.509132,
		-0.500000, -0.500000, 0.500000,0.848302, 0.509132,
		0.500000, -0.500000, 0.500000,0.340409, 0.502321,
		0.500000, -0.500000, -0.500000,0.594750, 0.502321,
		0.500000, 0.500000, -0.500000,0.594750, 0.752417,
		0.500000, 0.500000, 0.500000,0.340409, 0.752417,
		-0.500000, -0.500000, 0.500000,0.341044, 0.754030,
		0.500000, -0.500000, 0.500000,0.592683, 0.754030,
		0.500000, 0.500000, 0.500000,0.592683, 1.004126,
		-0.500000, 0.500000, 0.500000,0.341044, 1.004126
	};

	unsigned int index[]
	{
		//0,1,2,
		//0,3,1
		//
		0,1,2,
		0,2,3,
		4,5,6,
		4,6,7,
		8,9,10,
		8,10,11,
		12,13,14,
		12,14,15,
		16,17,18,
		16,18,19,
		20,21,22,
		20,22,2
	};

	glGenVertexArrays(1, &this->m_quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->m_quadVAO);
	

	VertexLayout layout;
	layout.Add<float>(3);
	layout.Add<float>(2);

	const std::vector<VertexElement>& elements = layout.GetElements();
	unsigned int offset = 0;
	
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto e = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.elementCount, e.dataType, e.isNormalized, layout.GetStride(), (const void*)offset);
		offset += e.elementCount * VertexElement::TypeSize(e.dataType);
	}


	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	m_Count = sizeof(index) / sizeof(index[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), index, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

SpriteRenderer::SpriteRenderer(Shader& shader)
{
	this->m_shader = shader;
	this->InitializeRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->m_quadVAO);
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec3 position, glm::vec3 size, float rotation, glm::vec3 color)
{
	this->m_shader.Bind();

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, position);

	//model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

	model = glm::scale(model, size);

	this->m_shader.SetUniformMat4f("u_model", model);
	this->m_shader.SetUniform3f("u_spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->m_quadVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
