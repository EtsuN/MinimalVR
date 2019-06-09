#ifndef LINE_H
#define LINE_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Line {
public:
	Line();
	~Line();
	GLfloat* vert;
	glm::mat4 toWorld;

	GLfloat verts[6] = {
  -0.5f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
	};

	void draw(GLuint shaderProgram, const glm::mat4& projection, const glm::mat4& view);
	void update();
	void spin(float);

	// These variables are needed for the shader program
	GLuint vertexBuffer, normalBuffer, VAO;
	GLuint uProjection, uModelview;
};

#endif
