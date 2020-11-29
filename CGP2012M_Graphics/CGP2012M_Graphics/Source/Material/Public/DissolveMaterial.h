#pragma once

#include <Material/Public/Material.h>

class DissolveMaterial : public Material
{
	
public:

	DissolveMaterial();

public:

	void BindTextureUniforms() override;
	void SetNoiseThreshold( const float InThreshold );

protected:

	void SetMaterialBuffers() override;
	void SetShaders() override;
	void SetTextures() override;

private:

	float NoiseThreshold;

};