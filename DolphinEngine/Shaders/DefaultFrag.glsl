#version 460

in vec3 outPosition;
in vec3 outNormal;
in vec2 outUV;
in vec3 outTangent;
in vec3 outBitangent;

in vec3 outWorldPosition;
in vec3 outWorldNormal;

out vec4 outColor;

layout(binding=0) uniform samplerCube uSkybox;
uniform vec3 uAmbientColor = vec3(.2);

uniform vec3 uCameraPos;

uniform vec4 uAlbedo = vec4(vec3(.5), 1);
layout(binding=1) uniform sampler2D uAlbedoTex;

uniform float uAlphaClip;

uniform vec3 uSpecular = vec3(.25);
layout(binding=2) uniform sampler2D uSpecularTex;
uniform float uShininess = 24;

struct Light
{
	int uType;
	vec3 uColor;
	vec3 uPosition;
	vec2 uFalloff;
};

uniform Light[5] uLights;

void main()
{
	vec4 albedo = texture(uAlbedoTex, outUV) + uAlbedo;
	if (albedo.a <= uAlphaClip) discard;

	vec3 finalColor = uAmbientColor * albedo.xyz;

	for (int i = 0; i < 5; i++)
	{
		vec3 lightDir = normalize(uLights[i].uPosition - outWorldPosition * min(uLights[i].uType, 1));

		float diffuseStrength = max(dot(lightDir, outWorldNormal), 0);
		vec3 diffuse = diffuseStrength * albedo.xyz * uLights[i].uColor;

		vec3 viewDir = normalize(uCameraPos - outWorldPosition);
		vec3 reflectDir = reflect(-lightDir, outWorldNormal);
		vec3 halfwayDir = normalize(viewDir + lightDir);

		float specularStrength = pow(max(dot(outWorldNormal, halfwayDir), 0), uShininess);
		vec3 specular = specularStrength * (uSpecular + texture(uSpecularTex, outUV).xyz) * uLights[i].uColor;

		float lightDistance = distance(uLights[0].uPosition, outWorldPosition);
		float attenuation = 1.0 / (1 + uLights[i].uFalloff.x * lightDistance + uLights[i].uFalloff.y * (lightDistance * lightDistance));
		finalColor += (diffuse + specular) * attenuation;
	}

	outColor = vec4(finalColor, albedo.a);
}