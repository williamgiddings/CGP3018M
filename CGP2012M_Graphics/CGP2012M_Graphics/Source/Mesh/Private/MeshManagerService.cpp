#include <Mesh/Public/MeshManagerService.h>
#include <MeshParser/Public/OBJParser.h>

MeshManagerService::MeshManagerService()
	: LoadedMeshes()
{
}

MeshManagerService::~MeshManagerService()
{
	LoadedMeshes.clear();
}

std::shared_ptr<Mesh> MeshManagerService::GetMesh( const char* RelativePath )
{
	std::string Path = OBJParser::GetStaticPath( RelativePath );
	
	std::map<const char*, std::shared_ptr<Mesh> >::iterator MapIterator = LoadedMeshes.find( RelativePath );

	if ( MapIterator != LoadedMeshes.end() )
	{
		return MapIterator->second;
	}
	else
	{
		auto LoadedMesh = std::make_shared<Mesh>( OBJParser::LoadModel( Path.c_str() ) );
		LoadedMeshes.insert( std::pair<const char*, std::shared_ptr<Mesh> >( RelativePath, LoadedMesh ) );
		return LoadedMesh;
	}
	
	return nullptr;
}
