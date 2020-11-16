#pragma once
#include <Mesh/Public/Mesh.h>
#include <vector>
#include <map>

class MeshManagerService 
{
public:

	MeshManagerService();
	~MeshManagerService();

	std::shared_ptr<Mesh> GetMesh( const char * RelativePath );

private:

	std::map< const char*, std::shared_ptr<Mesh> >		LoadedMeshes;

};