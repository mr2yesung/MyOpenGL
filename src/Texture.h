#pragma once

class Texture {
private:
	unsigned int texture;
	unsigned int slot;
public:
	Texture(const unsigned int slot = 0);
	~Texture();

	void Bind() const;
	void Unbind() const;

	void LoadTexture(const char* filePath);
private:
	void UploadTexture(const int width, const int height, const int nrChannels, const unsigned char* image);

	void CreateBaseTexture();
};