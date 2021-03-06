#include <Transform/Public/Transform.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform()
	: TranslationMatrix( 1.0f )
	, RotationMatrix( 1.0f )
	, ScaleMatrix( 1.0f )
	, Up( 0.0f, 1.0f, 0.0f )
	, Right( 1.0f, 0.0f, 0.0f )
{
}


glm::vec3 Transform::GetScale() const
{
	glm::vec3 LocalScale = glm::vec3( 0.0f );
	LocalScale.x = GetMatrix()[0][0];
	LocalScale.y = GetMatrix()[1][1];
	LocalScale.z = GetMatrix()[2][2];
	return LocalScale;
}

glm::vec3 Transform::GetPosition() const
{
	glm::vec3 LocalPosition = glm::vec3( 0.0f );
	LocalPosition.x = GetMatrix()[3][0];
	LocalPosition.y = GetMatrix()[3][1];
	LocalPosition.z = GetMatrix()[3][2];
	return LocalPosition;
}

glm::vec3 Transform::GetRotation() const
{
	const glm::mat4& TransformMatrix = GetMatrix();
	glm::vec3 LocalRotation = glm::vec3( 0.0f );
	LocalRotation.y = -asin( TransformMatrix[2][0] );

	if ( TransformMatrix[2][0] == 1 )
	{
		LocalRotation.x = 0.0f;
		LocalRotation.z = atan2( -TransformMatrix[0][1], -TransformMatrix[0][2] );
	}
	else if ( TransformMatrix[2][0] == -1 )
	{
		LocalRotation.x = 0.0f;
		LocalRotation.z = atan2( TransformMatrix[0][1], TransformMatrix[0][2] );
	}
	else
	{
		LocalRotation.x = atan2( TransformMatrix[1][0], TransformMatrix[0][0] );
		LocalRotation.z = atan2( TransformMatrix[2][1], TransformMatrix[2][2] );
	}
	return LocalRotation;
}

glm::mat4 Transform::GetMatrix() const
{
	return TranslationMatrix * RotationMatrix * ScaleMatrix;
}

void Transform::SetScale( const float InScale )
{
	ScaleMatrix = glm::scale( ScaleMatrix, glm::vec3( InScale ) );
}

void Transform::SetScale( const glm::vec3 InScale )
{
	ScaleMatrix = glm::scale( ScaleMatrix, InScale );
}

void Transform::SetRotation( const glm::vec3 InRotation )
{
	RotationMatrix = glm::eulerAngleYXZ( InRotation.x, InRotation.y, InRotation.z );
}

void Transform::SetPosition( const glm::vec3 InPosition )
{
	TranslationMatrix = glm::translate( TranslationMatrix, InPosition );
}

