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
	VertexLayout();

	template<typename T>
	void Add(unsigned int count);
	
	template<> void Add<float>(unsigned int count);
	template<> void Add<unsigned int>(unsigned int count);

	const std::vector<VertexElement> GetElements() const;
	unsigned int GetStride() const;
};