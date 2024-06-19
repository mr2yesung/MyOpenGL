#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;

out vec2 textureCoord;
out vec3 normal;

uniform mat4 view;
uniform mat4 projection;

void main()
{
   textureCoord = vertexTexture;

   normal = vertexNormal;

   gl_Position = projection * view * vec4(position, 1.0);
};

#shader fragment
#version 330 core

in vec2 textureCoord;
in vec3 normal;

out vec4 fragColor;

uniform sampler2D texture2d;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float ambientStrength;

void main()
{
	// ambient
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	// negative light is not defined
	float diffuseIntensity = max(dot(normalize(normal), normalize(-lightDirection)), 0.0);
	vec3 diffuse = lightColor * diffuseIntensity;

	// no specular because directional light

	vec4 textureColor = texture(texture2d, textureCoord);

	vec3 finalColor = textureColor.rgb * (ambient + diffuse);
	fragColor = vec4(finalColor, textureColor.a);
};