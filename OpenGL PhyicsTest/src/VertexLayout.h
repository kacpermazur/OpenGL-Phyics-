#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexElement
{
	unsigned int dataType;
	unsigned int elementCount;
	unsigned int isNormalized;

	static unsigned int TypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GL_FLOAT);
		case GL_UNSIGNED_INT:
			return sizeof(GL_UNSIGNED_INT);
		case GL_UNSIGNED_BYTE:
			return sizeof(GL_UNSIGNED_BYTE);
		}
		return 0;
	}
};

class VertexLayout
{
private:
	std::vector<VertexElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexLayout()
		:m_Stride(0)
	{
	}

	template <typename T>
	void Add(unsigned int count)
	{
		static_assert(false, "Unsupported Data Type");
	}

	template <>
	void Add<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });

		m_Stride += VertexElement::TypeSize(GL_FLOAT) * count;
	}

	template <>
	void Add<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });

		m_Stride += VertexElement::TypeSize(GL_UNSIGNED_INT) * count;
	}

	const std::vector<VertexElement> GetElements() const
	{
		return m_Elements;
	}

	unsigned int GetStride() const
	{
		return m_Stride;
	}

};