#include <Application/Public/ApplicationState.h>
#include <SceneObject/Public/SceneObject.h>
#include <Engine/Utils/Public/MathUtil.h>

SceneObject::SceneObject( ApplicationState* AppStateStrongPtr )
	: InstanceID()
	, LocalTransform()
	, AppState( AppStateStrongPtr )
{
	InstanceID = MathUtils::GenerateUUID();
}

void SceneObject::Render()
{
}

Transform& SceneObject::GetTransform()
{
	return LocalTransform;
}

std::string SceneObject::GetInstanceID() const
{
	return InstanceID;
}
