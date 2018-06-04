#pragma once

namespace Utils
{

	template < typename T >
	T Clamp(T l_value, T l_min, T l_max)
	{
		const T t = l_value < l_min ? l_min : l_value;
		return t > l_max ? l_max : t;
	}


	template <typename T>
	T SmoothStep(T l_min, T l_max, T l_value)
	{
		l_value = Clamp((l_value - l_min) / (l_max - l_min), -1.0f, 1.0f);
		return l_value*l_value*(3 - 2 * l_value);
	}
}

