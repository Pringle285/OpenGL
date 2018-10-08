//function creation in header
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <exception>
#include <GL/glew.h>
#include <vector>

GLuint createVertexShader();
GLuint createUniformFragmentShader();

GLuint createVBO(std::vector<GLfloat> shapePositions);
GLuint createAttVertexShader();
GLuint createAttFragmentShader();

