#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 vertNormal;
out vec3 vertPosition;

void main()
{
    vertNormal= mat3(transpose(inverse(model))) * normal;
	vertPosition = vec3(model * vec4(position.x, position.y, position.z, 1.0));
    
    gl_Position = projection * view * vec4(vertPosition, 1.0);
}
