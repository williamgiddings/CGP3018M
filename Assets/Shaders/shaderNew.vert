#version 440 core
layout (location = 0) in vec3 Position; //vertex positions
layout (location=1) in vec2 texCoord;	//texture coordinates
layout (location=2) in vec3 normals;	//vertex colours

out vec2 textureCoordinate;
out vec3 normalDirs; 						//output vertex colour to fragment shader
out vec3 fragmentPosition;

uniform mat4 uNormalMatrix;
uniform mat4 transform;				//pass transform matrix into the shader
uniform mat4 uView;	
uniform mat4 uProjection;


void main()
{
	gl_Position =  transform * vec4(Position, 1.0);
	fragmentPosition = vec3(transform * vec4(Position, 1.0f));
	normalDirs = mat3(uNormalMatrix)*normals; 	
	textureCoordinate = vec2(texCoord.x, 1-texCoord.y);
}