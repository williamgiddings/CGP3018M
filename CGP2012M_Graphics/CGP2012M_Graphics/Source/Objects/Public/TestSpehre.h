#pragma once
#include <SceneObject/Public/ScenePhysObject.h>

class TestSphere : public ScenePhysObject
{

public:

	TestSphere( ApplicationState* InAppState );

public:

	void Tick() override;

private:

	glm::vec3	CurrentRotation;
	glm::vec3	RotationAmount;
	float		RotationSpeed;

};