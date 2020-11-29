#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <memory>
#include <vector>

#include <Lighting/Public/LightSource.h>
#include <Texture/Public/Texture.h>

using UniformPairMat4 = std::pair< const char*, glm::mat4 >;
using UniformPairFloat1 = std::pair< const char*, float >;
using UniformPairInt = std::pair< const char*, int >;
using UniformPairLightArray = std::pair< const char*, std::vector< std::weak_ptr< LightSource > > >;
using UniformPairFloat4 = std::pair < const char*, glm::vec4 >;
class UniformBinding
{
public:

	UniformBinding();

public:

	UniformPairMat4				NormalMatrixBinding;
	UniformPairMat4				TransformBinding;
	UniformPairMat4				ProjectionMatrixBinding;
	UniformPairMat4				ViewMatrixBinding;
	UniformPairInt				SceneLightCount;
	UniformPairFloat4			SceneLightAmbient;
	UniformPairLightArray		SceneLights;
};
