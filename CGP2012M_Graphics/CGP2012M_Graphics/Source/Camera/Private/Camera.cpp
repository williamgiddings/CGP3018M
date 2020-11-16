#include <Camera/Public/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera( ApplicationState* AppStateStrongPtr )
	: SceneObject( AppStateStrongPtr )
	, CameraSpeed( 0.2f )
	, CameraTarget( 0.0f )
	, CameraViewMatrix( 0.0f )
{
}

void Camera::UpdateCamera()
{
	CameraViewMatrix = glm::lookAt( 
		GetPosition(),
		glm::normalize( GetPosition() - CameraTarget ),
		Up 
	);
}
