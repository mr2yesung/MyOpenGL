#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;

out vec2 textureCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * position;
   textureCoord = vertexTexture;
};

#shader fragment
#version 330 core

in vec2 textureCoord;

out vec4 fragColor;

uniform sampler2D texture2d;

void main()
{
   fragColor = texture(texture2d, textureCoord);
};