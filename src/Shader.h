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

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniformMatrix4fv(const std::string& name, const unsigned char transpose, const float* value);
	void SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3);
private:
	const ShaderSources ParseShader(const std::string& filePath) const;
	const unsigned int CompileShader(const unsigned int type, const std::string& source) const;
	const unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

	const int GetUniformLocation(const std::string& name);
};