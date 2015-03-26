#pragma once

namespace math
{
	const float PI = 3.141592653589793f;

	template<class T>
	T random(T min, T max);
}

inline float Deg2Rad(float angle)
{
    return angle * 0.017453292519943f;
}

inline float Rad2Deg(float angle)
{
    return angle * 57.295779513082321f;
}