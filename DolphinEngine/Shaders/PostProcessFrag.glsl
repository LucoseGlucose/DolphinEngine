#version 460

in vec2 outUV;

out vec4 outColor;

layout(binding=0) uniform sampler2D uSceneTex;

void main()
{
	vec4 sceneColor = texture(uSceneTex, outUV);
	outColor = sceneColor;
}