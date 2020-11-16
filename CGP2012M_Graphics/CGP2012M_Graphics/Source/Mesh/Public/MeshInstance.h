#pragma once
#include <GL/glew.h>

#include <Mesh/Public/Mesh.h>
#include <Shader/Public/Shader.h>
#include <Texture/Public/Texture.h>
#include <cstring>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class MeshInstance
{

public:

	enum VertexDrawModes
	{
		Tris,
		Quads
	};

private:

	std::shared_ptr<Mesh>	ObjectMesh;

	Shader					VertexShader;
	Shader					FragmentShader;

	bool					RenderWireframe;
	bool					FlipUVs;
	bool					ClearDepth;
	bool					MeshBuffersSet;

	VertexDrawModes			VertexDrawMode;
	GLuint					CompiledShader;

public:

	MeshInstance();
	MeshInstance( std::shared_ptr<Mesh> PooledMeshReference );

	void SetRenderType( const VertexDrawModes DrawMode );
	void Render();

private:

	void ApplyRenderSettings();
	void ApplyTextures();
};
