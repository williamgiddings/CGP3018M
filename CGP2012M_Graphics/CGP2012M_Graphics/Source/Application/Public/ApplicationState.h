#pragma once
#include <Engine/ObjectFactory/Public/ObjectManagerService.h>
#include <Input/Public/InputHandlerService.h>
#include <Mesh/Public/MeshManagerService.h>
#include <Lighting/Public/LightingService.h>

class TestSphere;
class Camera;
class ApplicationState
{
public:

	ApplicationState();

	std::weak_ptr<Camera> GetSceneCamera() const;
	InputHandlerService& GetInputHandlerService();
	MeshManagerService& GetMeshManagerService();
	ObjectManagerService& GetObjectManagerService();
	LightingService& GetLightingService();

	void StartGameState();
	void TickGameState();

private:

	InputHandlerService					InputHandlerServiceInstance;
	MeshManagerService					MeshManagerServiceInstance;
	ObjectManagerService				ObjectManagerServiceInstance;
	LightingService						LightingServiceInstance;

	std::weak_ptr<TestSphere>		Sphere;
	std::weak_ptr<Camera>				SceneCamera;
	std::weak_ptr<LightSource>			SceneLight;
};