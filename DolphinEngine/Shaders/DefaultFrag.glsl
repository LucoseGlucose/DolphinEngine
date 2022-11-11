#version 460

in vec3 outPosition;
in vec3 outNormal;
in vec2 outUV;
in vec3 outTangent;
in vec3 outBitangent;

out vec4 outColor;

uniform vec4 uAlbedo = vec4(0, 0, 0, 1);
layout(binding=0) uniform sampler2D uAlbedoTex;
uniform float uAlphaClip;
uniform vec3 uSpecular;
layout(binding=1) uniform sampler2D uSpecularTex;

void main()
{
	vec4 albedo = texture(uAlbedoTex, outUV) + uAlbedo;

	if (albedo.a <= uAlphaClip) discard;

	outColor = albedo;
}