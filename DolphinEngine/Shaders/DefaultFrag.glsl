#version 460

in vec3 outPosition;
in vec3 outNormal;
in vec2 outUV;
in vec3 outTangent;
in vec3 outBitangent;

out vec4 outColor;

uniform vec3 uAlbedo;
layout(binding=0) uniform sampler2D uAlbedoTex;
uniform float uAlpha = 1;
uniform vec3 uSpecular;
layout(binding=1) uniform sampler2D uSpecularTex;

void main()
{
	vec3 diffuse = texture(uAlbedoTex, outUV).xyz + uAlbedo;
	outColor = vec4(diffuse, uAlpha);
}