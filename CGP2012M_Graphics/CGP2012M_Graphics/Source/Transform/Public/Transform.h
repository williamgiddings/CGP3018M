#pragma once
#include <glm/glm.hpp>

class Transform
{

public:

	Transform();

	glm::vec3 GetScale() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::mat4 GetMatrix() const;

	void SetPosition( const float X, const float Y, const float Z );
	void SetPosition( const glm::vec3 InPosition );

public:

	glm::vec3		Up;
	glm::vec3		Right;

private:

	glm::mat4		TranslationMatrix;
	glm::mat4		RotationMatrix;
	glm::mat4		ScaleMatrix;

};