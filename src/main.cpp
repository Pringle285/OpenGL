#include "main.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Triangle",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (!SDL_GL_CreateContext(window))
  {
	  throw std::exception();
  }
  if (glewInit() != GLEW_OK)
  {
	  throw std::exception();
  }


  //creating positions
  VertexBuffer *positions1 = new VertexBuffer();
  positions1->add(glm::vec3(0.0f, 0.5f, 0.0f));
  positions1->add(glm::vec3(-0.9f, -0.9f, 0.0f));
  positions1->add(glm::vec3(0.5f, -0.5f, 0.0f));

  VertexBuffer *positions2 = new VertexBuffer();
  positions2->add(glm::vec3(0.5f, 0.0f, 0.0f));
  positions2->add(glm::vec3(0.2f, 0.8f, 0.0f));
  positions2->add(glm::vec3(0.8f, 0.2f, 0.0f));

  //creating colors
  VertexBuffer *colors1 = new VertexBuffer();
  colors1->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  colors1->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  colors1->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //creating the vertexArrays vaos
  VertexArray *shape1 = new VertexArray();
  shape1->SetBuffer("in_Position", positions1);
  shape1->SetBuffer("in_Color", colors1);

  VertexArray *shape2 = new VertexArray();
  shape2->SetBuffer("in_Position", positions2);
  shape2->SetBuffer("in_Color", colors1);


  ShaderProgram *shaderProgram = new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag");


  bool quit = false;
  //main draw loop
  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	shaderProgram->draw(shape1);
	shaderProgram->draw(shape2);

	SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}



//initial basic Vertex Shader
GLuint createVertexShader()
{
	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;            "\
		"                                       "\
		"void main()                            "\
		"{                                      "\
		"  gl_Position = vec4(in_Position, 1.0);"\
		"}                                      ";

	//Create a new vertex shader, attach source code, compile it and check for errors
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}
	return vertexShaderId;
}

//Vertex Shader to use Attribue Streams
GLuint createAttVertexShader()
{
	const GLchar *vertexShaderSrc = 
		"attribute vec3 in_Position;            "\
		"attribute vec4 in_Color;               "\
		"                                       "\
		"varying vec4 ex_Color;                 "\
		"void main()                            "\
		"{                                      "\
		"  gl_Position = vec4(in_Position, 1.0);"\
		"  ex_Color = in_Color;                 "\
		"}                                      ";
	//Create a new vertex shader, attach source code, compile it and check for errors
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}
	return vertexShaderId;
}

//Creating a uniform fragment shader
GLuint createUniformFragmentShader()
{
	const GLchar *fragmentShaderSrc =
		"uniform vec4 in_Color;            "\
		"void main()                       "\
		"{                                 "\
		"  gl_FragColor = in_Color;        "\
		"};                                ";

	//create a new fragment shader, attach source code, compile it and check for errors
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	GLint success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}
	return fragmentShaderId; 
}

//creating a attribute stream fragment shader
GLuint createAttFragmentShader()
{
	const GLchar *fragmentShaderSrc = 
		"varying vec4 ex_Color;            "\
		"void main()                       "\
		"{                                 "\
		"  gl_FragColor = ex_Color;        "\
		"};                                ";

	//create a new fragment shader, attach source code, compile it and check for errors
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	GLint success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}
	return fragmentShaderId;
}

GLuint createVBO(std::vector<GLfloat> shapePositions)
{
	GLuint positionsVboId = 0;

	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * shapePositions.size(), &shapePositions[0], GL_STATIC_DRAW);
	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return positionsVboId;
}
