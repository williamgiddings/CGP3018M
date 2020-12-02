#version 440 core
layout (location = 0) in vec3 InPosition;
layout (location=1) in vec2 InTexCoord;
layout (location=2) in vec3 InNormals;

out vec2 textureCoordinate;
out vec3 normalDirs;	
out vec3 fragmentPosition;

uniform mat4 uTransform;
uniform mat4 uView;	
uniform mat4 uProjection;
uniform mat4 uNormalMatrix;

void main()
{
	
	gl_Position = uProjection * uView * uTransform * vec4(InPosition, 1.0);
	fragmentPosition = vec3(uTransform * vec4(InPosition, 1.0f));
	textureCoordinate = vec2(InTexCoord.x, 1-InTexCoord.y);
	normalDirs = vec3(uNormalMatrix * vec4(InNormals, 0.0));
	
}