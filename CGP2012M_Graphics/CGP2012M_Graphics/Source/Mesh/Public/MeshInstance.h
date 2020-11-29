#pragma once
#include <GL/glew.h>
#include <cstring>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include <Material/Public/Material.h>
#include <Mesh/Public/Mesh.h>
#include <Shader/Public/Shader.h>
#include <Shader/Public/UniformBinding.h>
#include <Texture/Public/Texture.h>
#include <Material/Public/Material.h>

class ScenePhysObject;
class MeshInstance
{

public:

	enum VertexDrawModes
	{
		Tris,
		Quads
	};


public:
	
	MeshInstance( ScenePhysObject* InstanceOwner, const char* MeshName );

	void SetRenderType( const VertexDrawModes DrawMode );
	void Render();
	void SetUniformBindings( const UniformBinding InBinding );
	std::weak_ptr<Mesh> GetSharedMesh() const;
	std::weak_ptr<Material> GetMaterial() const;
	
	template< typename MaterialType >
	void SetMaterial( MaterialType InMaterial );


private:

	void LoadMesh( const char * MeshName );
	void ApplyShaderUniforms();
	void ApplyLightingUniforms();
	void ApplyRenderSettings();
	void ApplyTextures();

private:

	std::weak_ptr<Mesh>					ObjectMesh;
	std::shared_ptr<Material>			ObjectMaterial;

	bool								RenderWireframe;
	bool								FlipUVs;
	bool								ClearDepth;

	VertexDrawModes						VertexDrawMode;
	ScenePhysObject*					InstanceOwner;

	UniformBinding						UniformBindings;
};

template< typename MaterialType >
void MeshInstance::SetMaterial( MaterialType InMaterial )
{
	ObjectMaterial = std::shared_ptr<MaterialType>( new MaterialType( InMaterial ) );
}
