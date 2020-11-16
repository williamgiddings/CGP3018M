#pragma once
#include <GL/glew.h>
#include <cstring>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include <Mesh/Public/Mesh.h>
#include <Shader/Public/Shader.h>
#include <Texture/Public/Texture.h>

class ScenePhysObject;

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

	VertexDrawModes			VertexDrawMode;
	GLuint					CompiledShader;
	ScenePhysObject*		InstanceOwner;

public:

	MeshInstance();
	MeshInstance( ScenePhysObject* InstanceOwner, std::shared_ptr<Mesh> PooledMeshReference );

	void SetRenderType( const VertexDrawModes DrawMode );
	void Render();

private:

	void ApplyShaderUniforms();
	void ApplyRenderSettings();
	void ApplyTextures();
};
