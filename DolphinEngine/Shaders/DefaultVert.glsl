#version 460

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;
layout (location = 3) in vec3 inTangent;
layout (location = 4) in vec3 inBitangent;

out vec3 outPosition;
out vec3 outNormal;
out vec2 outUV;
out vec3 outTangent;
out vec3 outBitangent;

uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main()
{
	outPosition = inPosition;
	outNormal = inNormal;
	outUV = inUV;
	outTangent = inTangent;
	outBitangent = inBitangent;

	gl_Position =  uProjectionMat * uViewMat * uModelMat * vec4(inPosition, 1);
}