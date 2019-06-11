#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 vertNormal;
out vec3 vertPosition;
out vec2 vertTexture;

void main()
{
    vertNormal= mat3(transpose(inverse(model))) * normal;
	vertPosition = vec3(model * vec4(position.x, position.y, position.z, 1.0));
    vertTexture = texture;

    gl_Position = projection * view * vec4(vertPosition, 1.0);
}
