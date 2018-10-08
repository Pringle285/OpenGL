#include <GL/glew.h>
#include <string> 
#include <glm/glm.hpp>
#include <fstream>

class VertexArray;

class ShaderProgram
{
private:
	GLuint id; 
	

public:
	ShaderProgram(); //constructor
	~ShaderProgram(); //destructor

	ShaderProgram(std::string vert, std::string frag);

	void draw(VertexArray *vertexArray);
	void setUniform(std::string uniform, glm::vec4 value);
	void setUniform(std::string uniform, float value);
	GLuint getID();
	
protected:

};