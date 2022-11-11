#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

using namespace std;
using namespace glm;

inline vector<float> Expand(vector<vec3> v)
{
	vector<float> n = vector<float>(v.size() * 3);

	for (size_t i = 0; i < v.size(); i++)
	{
		n[i * 3] = v[i].x;
		n[i * 3 + 1] = v[i].y;
		n[i * 3 + 2] = v[i].z;
	}

	return n;
}

inline vector<float> Expand(vector<vec2> v)
{
	vector<float> n = vector<float>(v.size() * 2);

	for (size_t i = 0; i < v.size(); i++)
	{
		n[i * 2] = v[i].x;
		n[i * 2 + 1] = v[i].y;
	}

	return n;
}


inline quat GetQuat(vec3 angles)
{
    vec3 v = glm::radians(angles);

    float cy = (float)cos(v.z * 0.5);
    float sy = (float)sin(v.z * 0.5);
    float cp = (float)cos(v.y * 0.5);
    float sp = (float)sin(v.y * 0.5);
    float cr = (float)cos(v.x * 0.5);
    float sr = (float)sin(v.x * 0.5);

    return quat(cr * cp * cy + sr * sp * sy, sr * cp * cy - cr * sp * sy, cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy);
}

inline vec3 GetAngles(quat q)
{
    vec3 angles;

    double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
    double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
    angles.x = (float)atan2(sinr_cosp, cosr_cosp);

    double sinp = 2 * (q.w * q.y - q.z * q.x);
    if (abs(sinp) >= 1)
    {
        angles.y = (float)(pi<float>() / 2 * sign(sinp));
    }
    else
    {
        angles.y = (float)asin(sinp);
    }

    double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
    double cosy_cosp = 1 - 2 * (q.y * q.y + q.y * q.z);
    angles.z = (float)atan2(siny_cosp, cosy_cosp);

    return glm::degrees(angles);
}

inline mat4 GetMat4(vec3 angles)
{
    mat4 m = mat4(1.f);

    m = glm::rotate(m, glm::radians(angles.x), vec3(1.f, 0.f, 0.f));
    m = glm::rotate(m, glm::radians(angles.y), vec3(0.f, 1.f, 0.f));
    m = glm::rotate(m, glm::radians(angles.z), vec3(0.f, 0.f, 1.f));

    return m;
}