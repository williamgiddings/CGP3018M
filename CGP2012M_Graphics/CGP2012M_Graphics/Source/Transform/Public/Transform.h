#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

class Transform
{

public:

	Transform();

	glm::vec3 GetScale() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::mat4 GetMatrix() const;


	void SetScale( const float InScale );
	void SetScale( const glm::vec3 InScale );
	void SetPosition( const glm::vec3 InPosition );
	void SetRotation( const glm::vec3 InRotation );

public:

	glm::vec3		Up;
	glm::vec3		Right;

private:

	glm::mat4		TranslationMatrix;
	glm::mat4		RotationMatrix;
	glm::mat4		ScaleMatrix;

};