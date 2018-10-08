#include <vector>
#include <GL/glew.h>

class VertexBuffer;

class VertexArray
{
private:
	GLuint id; 
	bool dirty;
	std::vector<VertexBuffer*> buffers; //only 1 position/color per array
	//check where setBuffer is called in main, assigns the position and color to 
	//position 0 and 1 respectively. 
	//the vector is created in the array object to hold each buffer relevant to itself
	//for now this is position(0) and color(1), in the future this will also contain
	//things like textures

public:
	VertexArray(); //constructor
	~VertexArray(); //destructor

	void SetBuffer(std::string attribute, VertexBuffer *buffer);
	int GetVertexCount();
	GLuint GetID();

protected:
	
};