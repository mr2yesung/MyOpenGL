#pragma once

#include <string>
#include <unordered_map>

struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int shader;
	std::unordered_map<std::string, int> uniformLocationCache;
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// TODO: add uniform setters
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	ShaderSources ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};