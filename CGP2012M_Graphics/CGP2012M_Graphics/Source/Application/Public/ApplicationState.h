#pragma once
#include <Engine/ObjectFactory/Public/ObjectManagerService.h>
#include <Input/Public/InputHandlerService.h>
#include <Mesh/Public/MeshManagerService.h>

class ApplicationState
{
public:

	ApplicationState();


	InputHandlerService& GetInputHandlerService();
	MeshManagerService& GetMeshManagerService();
	ObjectManagerService& GetObjectManagerService();

	void StartGameState();
	void TickGameState();

private:

	InputHandlerService		InputHandlerServiceInstance;
	MeshManagerService		MeshManagerServiceInstance;
	ObjectManagerService	ObjectManagerServiceInstance;
};