#pragma once

#include <Material/Public/Material.h>

class DiffuseMaterial : public Material
{
	
public:

	DiffuseMaterial();

public:

	void BindTextureUniforms() override;

protected:

	void SetMaterialBuffers() override;
	void SetShaders() override;
	void SetTextures() override;

};