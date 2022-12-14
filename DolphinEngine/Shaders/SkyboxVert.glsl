#version 460

layout (location = 0) in vec3 inPosition;

out vec3 outPosition;

uniform mat4 uViewMat;
uniform mat4 uProjectionMat;

void main()
{
	outPosition = inPosition;
	vec4 pos = uProjectionMat * mat4(mat3(uViewMat)) * vec4(inPosition, 1);
	gl_Position =  pos.xyww;
}