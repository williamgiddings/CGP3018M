#version 440 core
in vec2 textureCoordinate; 
in vec3 normalDirs;	
in vec3 fragmentPosition;

out vec4 colour;

struct LightSource
{
	vec3 position;
	vec4 colour;
};

uniform vec4 uAmbientLight;
uniform LightSource uDynamicLights[10];
uniform int uLightCount;
uniform sampler2D uFirstTexture;		
uniform sampler2D uSecondTexture;		

void main()
{
	vec4 curColor = texture(uFirstTexture, textureCoordinate);
	vec3 lightingColor = vec3(0,0,0);
	vec3 objectAmbientReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = (uAmbientLight.a * objectAmbientReflectionCoeff) * vec3(uAmbientLight);

	for (int i = 0; i < uLightCount; ++i)
	{
		vec3 dLightColor = vec3(
			uDynamicLights[i].colour.x*uDynamicLights[i].colour.w,
			uDynamicLights[i].colour.y*uDynamicLights[i].colour.w,
			uDynamicLights[i].colour.z*uDynamicLights[i].colour.w);

		lightingColor = lightingColor*dLightColor;
		vec3 lightDirection = normalize(uDynamicLights[i].position - fragmentPosition);
		float diffuseStrength = max(dot(normalize(normalDirs), lightDirection), 0.0f);
		vec3 objectDiffuseReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
		vec3 diffuse = (diffuseStrength * objectDiffuseReflectionCoeff) * dLightColor;
		lightingColor.x += diffuse.x;
		lightingColor.y += diffuse.y;
		lightingColor.z += diffuse.z;
		
	}
	
	vec3 averagelight = vec3(0);
	
	if (uLightCount > 0)
	{
		averagelight = vec3(lightingColor.x/uLightCount, lightingColor.y/uLightCount, lightingColor.z/uLightCount);
	}

	vec4 newColour = vec4(
		(ambient.x+averagelight.x)*curColor.x,
		(ambient.x+averagelight.y)*curColor.y,
		(ambient.x+averagelight.z)*curColor.z,
		curColor.a);
	
	colour =  vec4(newColour.x+averagelight.x, newColour.y+averagelight.y, newColour.z+averagelight.z, curColor.a);

}


