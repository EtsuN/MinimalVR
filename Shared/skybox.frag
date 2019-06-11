#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.

in vec3 TexCoords;

uniform samplerCube skybox;
uniform int playerStat;

out vec4 fragColor;

void main()
{    
    vec4 color = texture(skybox, TexCoords);
	if (playerStat > 0) { // you lose
		color.y *= 0.5;
		color.z *= 0.5;
	}
	else if (playerStat < 0) { // you win
		color.x *= 0.7;
		color.y *= 0.7;
	}
	fragColor = color;
}
