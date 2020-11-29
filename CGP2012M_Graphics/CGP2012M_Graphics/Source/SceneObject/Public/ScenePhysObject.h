#pragma once
#include <SceneObject/Public/SceneObject.h>
#include <Mesh/Public/MeshInstance.h>

class ScenePhysObject : public SceneObject
{
public:

	ScenePhysObject( ApplicationState* AppStateStrongPtr, const char* MeshName );

	void Render() override;

private:

	UniformBinding GetUniformBindings();

protected:

	MeshInstance	ObjectMesh;
};