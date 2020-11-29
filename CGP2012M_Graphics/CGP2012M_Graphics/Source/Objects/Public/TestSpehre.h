#pragma once
#include <Engine/Utils/Public/PingPong.h>
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
	float		DissolveSpeed;
	float		CurrentDissolveThreshold;
	PingPong	PingPongInstance;

};