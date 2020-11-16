#pragma once
#include <SceneObject/Public/SceneObject.h>
#include <Mesh/Public/MeshInstance.h>

class ScenePhysObject : public SceneObject
{
public:

	ScenePhysObject( ApplicationState* AppStateStrongPtr, const char* MeshName );

	std::shared_ptr<Mesh> LoadMesh( const char* MeshName );
	void Render() override;

private:

	MeshInstance	ObjectMesh;
};