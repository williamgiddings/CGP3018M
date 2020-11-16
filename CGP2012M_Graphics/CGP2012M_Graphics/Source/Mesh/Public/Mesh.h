#pragma once

#include <GL/glew.h>
#include <Texture/Public/Texture.h>
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

public:

	Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode );

	void SetMeshBuffers();

	void SetLoadingMode( const VertexLoadingModes LoadingMode );
	void SetTexture( const char * InTextureFilePath );

	const VertexLoadingModes GetVertexReadMode() const;
	const std::vector<float>& GetVerticies() const;
	const std::vector<float>& GetUVCoords() const;
	const std::vector<float>& GetNormals() const;
	const std::vector<GLuint>& GetIndicies() const;
	
	const Texture& GetMeshTexture() const;

	GLuint GetVertexBuffer() const;
	GLuint GetIndexBuffer() const;
	GLuint GetVertexArrayObject() const;

private:

	std::vector<float>		Verticies;
	std::vector<float>		UVCoords;
	std::vector<float>		Normals;
	std::vector<GLuint>		Indicies;

	GLuint					VertexBufferObject;
	GLuint					IndexBufferObject;
	GLuint					VertexArrayObject;

	Texture					MeshTexture;
	VertexLoadingModes		VertexLoadingMode;

};