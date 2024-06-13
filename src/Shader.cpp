#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

Shader::Shader(const std::string& filePath)
	:shader(0)
{
    ShaderSources sources = ParseShader(filePath);

    shader = CreateShader(sources.VertexSource, sources.FragmentSource);

    Bind();
}

Shader::~Shader()
{
    glDeleteProgram(shader);
}

void Shader::Bind() const
{
    glUseProgram(shader);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

ShaderSources Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                shaderType = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                shaderType = ShaderType::FRAGMENT;
        }
        else if (shaderType != ShaderType::NONE)
        {
            ss[(int)shaderType] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    /* Error handling */
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Error compiling shader: " << message << std::endl;

        glDeleteShader(shader);

        delete[] message;

        return 0;
    }

    return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    int location = glGetUniformLocation(shader, name.c_str());
    if (location == -1)
        std::cout << "Warning: Uniform '" << name << "' does not exist" << std::endl;
    else
        uniformLocationCache[name] = location;

    return location;
}