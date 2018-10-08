#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <exception>


class VertexBuffer
{
private:
	GLuint id; 
	int components;
	std::vector<GLfloat> data; 
	bool dirty;

public:
	VertexBuffer(); //constructor
	~VertexBuffer(); //destructor

	void add(glm::vec3 value);
	void add(glm::vec4 value);

	int GetComponents();
	int GetDataSize();
	GLuint GetID();

protected:
	
};
