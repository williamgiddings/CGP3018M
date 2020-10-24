#pragma once
#include <GL/glew.h>

#include <Shader/Public/Shader.h>
#include <Texture/Public/Texture.h>
#include <cstring>
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
public:

	enum VertexLoadingModes
	{
		Indexed,
		Array
	};

	enum VertexDrawModes
	{
		Tris,
		Quads
	};

private:

	std::vector<float>		Verticies;
	std::vector<float>		UVCoords;
	std::vector<float>		Normals;
	std::vector<GLuint>		Indicies;
	
	Texture					MeshTexture;
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
	bool					ClearDepth;

public:

	Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode );

	void SetTexture( const char * InTextureFilePath );
	void SetRenderMode( const VertexLoadingModes LoadingMode );
	void SetRenderType( const VertexDrawModes DrawMode );
	void SetMeshBuffers();
	void Render();

private:

	void ApplyRenderSettings();
	void ApplyTextures();
};
