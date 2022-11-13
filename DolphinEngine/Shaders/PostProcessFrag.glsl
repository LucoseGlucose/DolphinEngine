#version 460

in vec2 outUV;

out vec4 outColor;

layout(binding=1) uniform sampler2D uColorTex;
layout(binding=2) uniform sampler2D uNormalTex;
layout(binding=3) uniform sampler2D uMaterialTex;
layout(binding=4) uniform sampler2D uDepthTex;

void main()
{
	outColor = texture(uColorTex, outUV);
}