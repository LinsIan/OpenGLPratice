#include "Texture.h"
#include "stb/stb_image.h"

#include <iostream>

Texture::Texture(const std::string& path, bool isFullPath /*= false*/, const std::string& typeName /*= ""*/, int filtering /*= GL_LINEAR*/, int wrapping /*= GL_CLAMP_TO_EDGE*/)
	: rendererID(0), filePath(path), localBuffer(nullptr), width(0), height(0), bitPerPixel(0), filteringMode(filtering), wrappingMode(wrapping)
{
#ifdef __APPLE__
	if (!isFullPath)
		filePath = "../" + path;
#endif

	this->typeName = typeName;
	type = GL_TEXTURE_2D;

	stbi_set_flip_vertically_on_load(1);
	// desired_channels for RGBA is 4
	localBuffer = stbi_load(filePath.c_str(), &width, &height, &bitPerPixel, 4);

	if (!localBuffer)
	{
		std::cout << "Failed to load texture file " << filePath << std::endl;
	}

	// create texture
	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

	// set texture parameter
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping));

	// set texture data
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Texture::Texture(std::vector <std::string> faces, bool isFullPath /*= false*/, const std::string& typeName /*= ""*/, int filtering /*= GL_LINEAR*/, int wrapping /*= GL_CLAMP_TO_EDGE*/)
	: rendererID(0), localBuffer(nullptr), width(0), height(0), bitPerPixel(0), filteringMode(filtering), wrappingMode(wrapping)
{
#ifdef __APPLE__
	if (!isFullPath)
		for (auto& face : faces)
			face = "../" + face;
#endif

	this->typeName = typeName;

	type = GL_TEXTURE_CUBE_MAP;
	stbi_set_flip_vertically_on_load(0);
	glGenTextures(1, &rendererID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, rendererID);
	
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		localBuffer = stbi_load(faces[i].c_str(), &width, &height, &bitPerPixel, 0);
		if (localBuffer)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
			stbi_image_free(localBuffer);
		}
		else
		{
			std::cout << "Failed to load cubemap texture at path: " << faces[i] << std::endl;
			stbi_image_free(localBuffer);
		}
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filtering));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filtering));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapping));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapping));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapping));
}

Texture::Texture(unsigned int textureID)
{
	type = GL_TEXTURE_2D;
    rendererID = textureID;
    width = 0;
    height = 0;
    bitPerPixel = 0;
	localBuffer = nullptr;
    filteringMode = GL_LINEAR;
    wrappingMode = GL_CLAMP_TO_EDGE;
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &rendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(type, rendererID));
}

void Texture::UnBind() const
{
    GLCall(glBindTexture(type, 0));
}


