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
uniform float uDissolveThreshold;
uniform sampler2D uFirstTexture;		
uniform sampler2D uSecondTexture;		
uniform sampler2D uNoiseTexture;	
uniform sampler2D uRampTexture;	

vec3 GetLighting()
{
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
		averagelight = lightingColor/uLightCount;
	}

	return averagelight + ambient;
}

void clip( float Value )
{
	if ( Value <= 0.0f )
	{
		discard;
	}
}

vec4 Dissolve()
{
	
	float BurnStep = 0.15f;
	float BurnMaskCuttoff = 2.75f;
	float GlowStep = 0.05f;
	vec4 Noise = texture( uNoiseTexture, textureCoordinate );
    
	float DissolveAmount = ( Noise.x - uDissolveThreshold );
    float IsVisible = step( DissolveAmount, GlowStep );
    float IsMasked = DissolveAmount >= -GlowStep*BurnMaskCuttoff ? 1.0f : 0.0f;
	
	float RampValue = DissolveAmount * (1 / BurnStep);
	vec4 BurnRamp = texture( uRampTexture, vec2(1-RampValue, 0) );
    vec4 Emission = BurnRamp * IsVisible * IsMasked;
    
    vec4 First = texture( uFirstTexture, textureCoordinate);
    vec4 Second = texture( uSecondTexture, textureCoordinate );
    
	vec4 FragColour = mix(First, Second, smoothstep( DissolveAmount, 0.0f, 1.0f ) );

	return FragColour + Emission;

}

void main()
{
	vec4 curColor = Dissolve();
	
	vec4 averagelight = vec4( GetLighting(), 1.0f );
	vec4 newColour = averagelight * curColor;

	colour = newColour;
}
