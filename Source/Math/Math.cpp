#include "stdafx.h"

#include <random>

namespace math
{
	static std::mt19937 rng(98934);

	template<class T>
	T random(T min_value, T max_value)
	{
		std::uniform_real_distribution<T> dist(min_value, max_value);
		return dist(rng);
	}
}