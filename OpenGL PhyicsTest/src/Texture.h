#pragma once

class Texture
{
public:
	unsigned int m_BindID;
	
	unsigned int m_width, m_height, m_bitsPerPixel;
	
	unsigned int m_internal_format;
	unsigned int m_image_format;

	unsigned int m_wrap_S;
	unsigned int m_wrap_T;
	unsigned int m_filter_min;
	unsigned int m_filter_max;

	Texture();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind() const;
};