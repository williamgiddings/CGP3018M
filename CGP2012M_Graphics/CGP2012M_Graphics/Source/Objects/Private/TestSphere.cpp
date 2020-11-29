#include <Objects/Public/TestSpehre.h>
#include <Material/Public/DissolveMaterial.h>

TestSphere::TestSphere( ApplicationState* InAppState )
	: ScenePhysObject( InAppState, "sphere.obj" )
	, CurrentRotation()
	, RotationAmount( glm::vec3(1.0f, 0.0f, 0.0f) )
	, RotationSpeed( 0.0f )
	, CurrentDissolveThreshold( 0.0f )
	, DissolveSpeed( 0.01f )
	, PingPongInstance( -0.3f, 1.3f )
{
	ObjectMesh.SetMaterial<DissolveMaterial>( DissolveMaterial() );
}

void TestSphere::Tick()
{
	glm::vec3 NewRotation = CurrentRotation += ( RotationAmount * RotationSpeed );
	SetRotation( NewRotation );

	if ( auto MaterialWeakPtr = ObjectMesh.GetMaterial().lock() )
	{
		if ( DissolveMaterial* DissolveMaterialStrong = ( DissolveMaterial* ) MaterialWeakPtr.get() )
		{
			DissolveMaterialStrong->SetNoiseThreshold( PingPongInstance.Advance( DissolveSpeed ) );
		}
	}

}

