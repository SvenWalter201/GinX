#include "gxpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "stb_image.h"

namespace GinX
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		GX_CORE_ASSERT(data, "Failed to load Texture");

		m_Width = width;
		m_Height = height;

		GLenum textureFormat  = 0, interpretedFormat = 0;

		switch (channels)
		{
		case 1:
		{
			textureFormat = GL_RED;
			interpretedFormat = GL_RGB;
			break;
		}
		case 3:
		{
			textureFormat = GL_RGB8;
			interpretedFormat = GL_RGB;
			break;
		}
		case 4:
		{
			textureFormat = GL_RGBA8;
			interpretedFormat = GL_RGBA;
			break;
		}
		}

		GX_CORE_ASSERT(textureFormat & interpretedFormat, "Texture Format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, textureFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, interpretedFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}
