#include "VertexLayout.h"


VertexLayout::VertexLayout()
	:m_Stride(0)
{
}

template <typename T>
void VertexLayout::Add(unsigned count)
{
	static_assert(false, "Unsupported Data Type");
}

template <>
void VertexLayout::Add<float>(unsigned count)
{
	m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });

	m_Stride += VertexElement::TypeSize(GL_FLOAT) * count;
}

template <>
void VertexLayout::Add<unsigned int>(unsigned count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });

	m_Stride += VertexElement::TypeSize(GL_UNSIGNED_INT) * count;
}

const std::vector<VertexElement> VertexLayout::GetElements() const
{
	return m_Elements;
}

unsigned VertexLayout::GetStride() const
{
	return m_Stride;
}
