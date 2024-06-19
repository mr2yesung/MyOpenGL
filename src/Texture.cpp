#include "Texture.h"

#include <GL/glew.h>
#include "stb_image.h"
#include <iostream>

Texture::Texture(const unsigned int slot)
	:slot(slot)
{
	glGenTextures(1, &texture);

	Bind();

	// texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	CreateBaseTexture();
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &texture);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadTexture(const char* filePath)
{
	int width, height, nrChannels;

	std::cout << "Loading png texture from " << filePath << std::endl;

	unsigned char* image = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (image)
	{
		UploadTexture(width, height, nrChannels, image);

		stbi_image_free(image);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
}

void Texture::UploadTexture(const int width, const int height, const int nrChannels, const unsigned char* image)
{
    unsigned int format = GL_RGB; // base nrChannels == 3
    if (nrChannels == 1) format = GL_RED;
    else if (nrChannels == 4) format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
}

void Texture::CreateBaseTexture()
{
    const int width = 1, height = 1, nrChannels = 3;

    unsigned char* image = new unsigned char[width * height * nrChannels];

    for (unsigned int i = 0; i < width * height * nrChannels; ++i)
    {
        // set base texture to full white
        image[i] = 255;
    }

    if (image)
    {
        UploadTexture(width, height, nrChannels, image);

        delete[] image;
    }
    else
        std::cout << "Failed to create base texture" << std::endl;
}
