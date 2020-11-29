#pragma once
#include <vector>
#include <map>

#include <Application/Public/ApplicationService.h>
#include <Mesh/Public/Mesh.h>

class MeshManagerService : public ApplicationService
{
public:

	MeshManagerService( ApplicationState* InAppState );
	~MeshManagerService();

public:

	std::weak_ptr<Mesh> GetMesh( const char * RelativePath );

private:

	std::map< const char*, std::shared_ptr<Mesh> >		LoadedMeshes;

};