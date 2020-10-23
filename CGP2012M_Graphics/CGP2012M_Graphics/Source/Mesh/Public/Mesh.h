#pragma once
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include "Shader/Public/ShaderClass.h"
#include <glm/glm.hpp>


class Mesh
{
public:

	enum class VertexLoadingModes
	{
		Indexed,
		Array,
		Max
	};

	enum class VertexDrawModes
	{
		Tris,
		Quads,
		Max
	};

private:

	std::vector<float>		Verticies;
	std::vector<float>		UVCoords;
	std::vector<float>		Normals;
	std::vector<GLuint>		Indicies;
	
	//Texture				MeshTexture;
	Shader					VertexShader;
	Shader					FragmentShader;

	bool					RenderWireframe;
	bool					FlipUVs;
	
	VertexLoadingModes		VertexLoadingMode;
	VertexDrawModes			VertexDrawMode;

	GLuint					CompiledShader;
	GLuint					VertexBufferObject;
	GLuint					VertexArrayObject;
	GLuint					IndexBufferObject;
	bool					IsTextureLoaded;
	bool					ClearDepth;

public:

	Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode );

	void SetTexture( const char* texturePath );
	void SetRenderMode( const VertexLoadingModes LoadingMode );
	void SetRenderType( const VertexDrawModes DrawMode );
	void SetMeshBuffers();
	void Render();
};
