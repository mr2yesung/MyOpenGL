#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;

void main()
{
   gl_Position = pos;
};

#shader fragment
#version 330 core

out vec4 fragColor;

uniform vec4 uColor;

void main()
{
   fragColor = uColor;
};