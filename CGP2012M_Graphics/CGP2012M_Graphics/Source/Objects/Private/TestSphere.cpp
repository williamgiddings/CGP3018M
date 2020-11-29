#include <Objects/Public/TestSpehre.h>
#include <Material/Public/DiffuseMaterial.h>

TestSphere::TestSphere( ApplicationState* InAppState )
	: ScenePhysObject( InAppState, "sphere.obj" )
	, CurrentRotation()
	, RotationAmount( glm::vec3(1.0f, 0.0f, 0.0f) )
	, RotationSpeed( 0.01f )
{
	ObjectMesh.SetMaterial<DiffuseMaterial>( DiffuseMaterial() );
}

void TestSphere::Tick()
{
	glm::vec3 NewRotation = CurrentRotation += ( RotationAmount * RotationSpeed );
	SetRotation( NewRotation );
}
