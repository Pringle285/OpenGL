#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	dirty = false; 

	buffers.resize(10);

	glGenVertexArrays(1, &id);

	if (!id)
	{
		throw std::exception();
	}
}

VertexArray::~VertexArray()
{

}

void VertexArray::SetBuffer(std::string attribute, VertexBuffer *buffer)
{
	if (attribute == "in_Position")
	{
		buffers.at(0) = buffer;
	}
	else if (attribute == "in_Color")
	{
		buffers.at(1) = buffer; 
	}
	else
	{
		throw std::exception();
	}

	dirty = true; 
}

int VertexArray::GetVertexCount()
{
	if (!buffers.at(0))
	{
		throw std::exception();
	}

	//this returns the number of vertex by getting the data size divided by the number
	//of componenets that were included in the vertexBuffer
	return buffers.at(0)->GetDataSize() / buffers.at(0)->GetComponents(); 
}

GLuint VertexArray::GetID()
{
	if (dirty)
	{
		glBindVertexArray(id);
		
		for (int i = 0; i < buffers.size(); i++)
		{
			if (buffers.at(i))
			{
				glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->GetID());
				glVertexAttribPointer(i, buffers.at(i)->GetComponents(), 
					GL_FLOAT, GL_FALSE, buffers.at(i)->GetComponents() * sizeof(GLfloat), (void *)0);
				glEnableVertexAttribArray(i);
			}
		}
	}

	return id;
}

