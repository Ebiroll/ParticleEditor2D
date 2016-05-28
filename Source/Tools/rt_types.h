#pragma once

#include <stdint.h>

namespace vis
{
	template<typename T> T min(const T& x, const T& y);
	template<typename T> T max(const T& x, const T& y);
	
	template<typename T> T abs(const T& x);
	template<typename T> T clamp(const T& x, const T& x_min, const T& x_max);




	////////////////////////////////////////////////////////////////

	template<typename T>
	inline T min(const T& x, const T& y)
	{
		return x < y ? x : y;
	}

	template<typename T>
	inline T max(const T& x, const T& y)
	{
		return x > y ? x : y;
	}

	template<typename T>
	inline T abs(const T& x)
	{
		return x >= T(0) ? x : -x;
	}

	template<typename T>
	inline T clamp(const T& x, const T& x_min, const T& x_max)
	{
		return x < x_min ? x_min : (x > x_max ? x_max : x);
	}
}