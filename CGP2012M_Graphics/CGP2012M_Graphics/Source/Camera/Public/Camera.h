#pragma once
#include <glm/glm.hpp>
#include <SceneObject/Public/SceneObject.h>

class Camera : public SceneObject
{

public:

	Camera( ApplicationState* AppStateStrongPtr );
	
	void UpdateCamera();

private:

	glm::vec3		CameraTarget;
	glm::mat4		CameraViewMatrix;
	float			CameraSpeed;
};
