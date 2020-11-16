#include <Application/Public/ApplicationState.h>
#include <SceneObject/Public/SceneObject.h>
#include <Engine/Utils/Public/MathUtil.h>

SceneObject::SceneObject( ApplicationState* AppStateStrongPtr )
	: InstanceID()
	, AppState( AppStateStrongPtr )
{
	InstanceID = MathUtils::GenerateUUID();
}

void SceneObject::Render()
{
}

std::string SceneObject::GetInstanceID() const
{
	return InstanceID;
}
