#include "Texture.h"

Texture::Texture()
	: m_width(0), m_height(0), m_internal_format(GL_RGB), m_image_format(GL_RGB), m_wrap_S(GL_REPEAT), m_wrap_T(GL_REPEAT), m_filter_min(GL_LINEAR), m_filter_max(GL_LINEAR)
{
	glGenBuffers(1, &this->m_BindID);
}

void Texture::Generate(unsigned width, unsigned height, unsigned char* data)
{
	this->m_width = width;
	this->m_height = height;

	glBindTexture(GL_TEXTURE_2D, this->m_BindID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_internal_format, width, height, 0, this->m_image_format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_filter_max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->m_BindID);
}
