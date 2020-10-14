#pragma once
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include "Shader/Public/ShaderClass.h"
#include <glm/glm.hpp>

#define RENDER_MODE_INDEXED 0
#define RENDER_MODE_ARRAY 1
#define RENDER_TYPE_TRI 0
#define RENDER_TYPE_QUAD 1

class Mesh
{

private:
	
	bool textureLoaded = false;

public:
	std::vector<float> verts;
	std::vector<float> uvcoords;
	std::vector<float> normals;
	std::vector<GLuint> indices;
	bool renderWire = false;
	bool flipUVs = false;
	int renderMode = 0; 
	int renderType = 0;
	//Texture tex;
	bool clearDepth = true;
	Shader vSh1, fSh1;
	GLuint shaderProgram1;

	GLuint VBO;
	GLuint VAO;
	GLuint IBO;

	Mesh( std::vector<float> v, std::vector<unsigned int> i, int rendermode ) 
		: verts(v) 
		, indices(i) 
		, renderMode(rendermode)
	{
		vSh1.shaderFileName("..//Assets//Shaders//shader_projection.vert");
		fSh1.shaderFileName("..//Assets//Shaders//shader_projection.frag");

		vSh1.getShader(1);
		fSh1.getShader(2);

		shaderProgram1 = glCreateProgram();
		glAttachShader(shaderProgram1, vSh1.shaderID);
		glAttachShader(shaderProgram1, fSh1.shaderID);
		glLinkProgram(shaderProgram1);

		glDeleteShader(vSh1.shaderID);
		glDeleteShader(fSh1.shaderID);
	};

	/*void SetTexture(const char* texturePath)
	{
		tex.load(texturePath);
		tex.setBuffers();
		textureLoaded = true;
	}*/

	void SetRenderMode(int rm)
	{
		renderMode = rm;
	}
	void SetRenderType(int rt)
	{
		renderType = rt;
	}
	void setBuffers()
	{
		//Create Vertex Array Object
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	
		//Create vertex buffer
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verts.size()* sizeof(float), &verts[0], GL_STATIC_DRAW);
	

		//Assign Attributes
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//Create index buffer
		if (renderMode == RENDER_MODE_INDEXED)
		{
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		}
		
		glBindVertexArray(0);
	}


	void Render ()
	{
		glUseProgram(shaderProgram1);
		glEnable(GL_BLEND);
		glCullFace(GL_BACK);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		if (!clearDepth)
		{
			glDisable(GL_DEPTH_TEST);
			
		}

		glBindVertexArray(VAO);
		if (textureLoaded)
		{
			//glBindTexture(GL_TEXTURE_2D, tex.texture);
		}
		
		glPointSize(5.0f);
		if (renderWire)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (renderType == RENDER_TYPE_QUAD)
		{
			if (renderMode == RENDER_MODE_INDEXED)
			{
				glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_QUADS, 0, verts.size());
			}

		}
		else
		{
			if (renderMode == RENDER_MODE_INDEXED)
			{
				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, verts.size());
			}
		}
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
};
