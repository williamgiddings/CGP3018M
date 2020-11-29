#pragma once
#include <glm/glm.hpp>
#include <SceneObject/Public/SceneObject.h>

class Camera : public SceneObject
{

public:

	Camera( ApplicationState* AppStateStrongPtr );

	
	void SetCameraPosition( const glm::vec3 InPos );
	void SetCameraTarget( const glm::vec3 LookTarget );
	void Tick() override;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

private:

	glm::vec3		CameraTarget;
	glm::mat4		CameraViewMatrix;
	float			CameraFOV;
	float			CameraSpeed;
};
