#version 440 core
in vec2 textureCoordinate; //tex coords from vertex shader
in vec3 normalDirs;			//input the Colour values from Vertex shader
in vec3 fragmentPosition;
out vec4 colour;

uniform vec4 testCol;
uniform vec3 testPos;
uniform sampler2D aTex;		//uniform holding texture info from main programme
uniform vec4 tint;
uniform vec4 randomColor;

void main()
{
    vec4 tintColor = vec4(tint.x, tint.y,tint.z, 0); 
	vec4 texColor = texture(aTex, textureCoordinate);
	vec4 curColor = texColor + tintColor;

	colour = vec4(curColor.x,curColor.y,curColor.z, curColor.a);

}


