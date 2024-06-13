#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 vColor;

void main()
{
   gl_Position = position;
   vColor = color;
};

#shader fragment
#version 330 core

out vec4 fragColor;
in vec3 vColor;

void main()
{
   fragColor = vec4(vColor, 1.0);
};