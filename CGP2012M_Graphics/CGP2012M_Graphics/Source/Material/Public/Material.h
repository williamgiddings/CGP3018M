#pragma once
#include <memory>
#include <vector>

#include <Shader/Public/Shader.h>

class Texture;
class Material
{
public:

	Material();

public:

	GLuint GetCompiledShader() const;
	virtual void BindTextureUniforms();

protected:
	
	virtual void SetMaterialBuffers();
	virtual void SetShaders();
	virtual void SetTextures();


protected:

	Shader						VertexShader;
	Shader						FragmentShader;
	GLuint						CompiledShader;
	std::vector<Texture>		StoredTextures;

};
