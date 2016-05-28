#pragma once

#include "rt_types.h"
//#include "math.h"

namespace vis
{
	template<typename T> struct Vector3;
	template<typename T> struct Vector4;

	template<typename T>
	struct Vector3
	{
		T x, y, z;

		Vector3();
		Vector3(const Vector3<T>& v);

		explicit Vector3(const T* v);
		explicit Vector3(T x);
		explicit Vector3(T x, T y, T z);

		explicit Vector3(const Vector4<T>& v);

		T& operator[](const uint32_t i);
		const T& operator[](const uint32_t i) const;

		Vector3<T>& operator=(const Vector3<T>& v);

		Vector3<T>& operator+=(T s);
		Vector3<T>& operator+=(const Vector3<T>& v);
		Vector3<T>& operator-=(T s);
		Vector3<T>& operator-=(const Vector3<T>& v);
		Vector3<T>& operator*=(T s);
		Vector3<T>& operator*=(const Vector3<T>& v);
		Vector3<T>& operator/=(T s);
		Vector3<T>& operator/=(const Vector3<T>& v);
	};

	typedef Vector3<float> Vector3_f;

	template<typename T> Vector3<T> operator-(const Vector3<T>& v);

	template<typename T> Vector3<T> operator+(T s, const Vector3<T>& v);
	template<typename T> Vector3<T> operator+(const Vector3<T>& v, T s);
	template<typename T> Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> Vector3<T> operator-(T s, const Vector3<T>& v);
	template<typename T> Vector3<T> operator-(const Vector3<T>& v, T s);
	template<typename T> Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> Vector3<T> operator*(T s, const Vector3<T>& v);
	template<typename T> Vector3<T> operator*(const Vector3<T>& v, T s);
	template<typename T> Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> Vector3<T> operator/(T s, const Vector3<T>& v);
	template<typename T> Vector3<T> operator/(const Vector3<T>& v, T s);
	template<typename T> Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2);

	template<typename T> T dot(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> T length(const Vector3<T>& v);
	template<typename T> T distance(const Vector3<T>& v1, const Vector3<T>& v2);
	template<typename T> Vector3<T> normalize(const Vector3<T>& v);
	template<typename T> Vector3<T> normalize(const Vector3<T>& v1, T& len);
	template<typename T> Vector3<T> mix(const Vector3<T>& v1, const Vector3<T>& v2, T s);

	template<typename T> Vector3<T> min(const Vector3<T>& v1, const Vector3<T>& v2);
    template<typename T> Vector3<T> max(const Vector3<T>& v1, const Vector3<T>& v2);
	////////////////////////////////////////////////////////////////
	template<typename T>
	struct Vector4
	{
		T x, y, z, w;

		Vector4();
		Vector4(const Vector4<T>& v);

		explicit Vector4(const T* v);
		explicit Vector4(T x, T y, T z, T w);

		explicit Vector4(const Vector3<T>& v, T w = T(0));

		T& operator[](const uint32_t i);
		const T& operator[](const uint32_t i) const;

		Vector4<T>& operator=(const Vector4<T>& v);

		Vector4<T>& operator+=(T s);
		Vector4<T>& operator+=(const Vector4<T>& v);
		Vector4<T>& operator-=(T s);
		Vector4<T>& operator-=(const Vector4<T>& v);
		Vector4<T>& operator*=(T s);
		Vector4<T>& operator*=(const Vector4<T>& v);
		Vector4<T>& operator/=(T s);
		Vector4<T>& operator/=(const Vector4<T>& v);
	};

	typedef Vector4<float> Vector4_f;

	template<typename T> Vector4<T> operator-(const Vector4<T>& v);

	template<typename T> Vector4<T> operator+(T s, const Vector4<T>& v);
	template<typename T> Vector4<T> operator+(const Vector4<T>& v, T s);
	template<typename T> Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> Vector4<T> operator-(T s, const Vector4<T>& v);
	template<typename T> Vector4<T> operator-(const Vector4<T>& v, T s);
	template<typename T> Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> Vector4<T> operator*(T s, const Vector4<T>& v);
	template<typename T> Vector4<T> operator*(const Vector4<T>& v, T s);
	template<typename T> Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> Vector4<T> operator/(T s, const Vector4<T>& v);
	template<typename T> Vector4<T> operator/(const Vector4<T>& v, T s);
	template<typename T> Vector4<T> operator/(const Vector4<T>& v1, const Vector4<T>& v2);

	template<typename T> T dot(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> T length(const Vector4<T>& v);
	template<typename T> T distance(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> Vector4<T> normalize(const Vector4<T>& v);
	template<typename T> Vector4<T> normalize(const Vector4<T>& v1, T& len);
	template<typename T> Vector4<T> min(const Vector4<T>& v1, const Vector4<T>& v2);
	template<typename T> Vector4<T> max(const Vector4<T>& v1, const Vector4<T>& v2);



	////////////////////////////////////////////////////////////////
	template<typename T>
	Vector3<T>::Vector3()
	{
	}

	template<typename T>
	Vector3<T>::Vector3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(const T* v) : x(v[0]), y(v[1]), z(v[2])
	{
	}

	template<typename T>
	Vector3<T>::Vector3(T x) : x(x), y(x), z(x)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z)
	{

	}

	template<typename T>
	T& Vector3<T>::operator[](const uint32_t i)
	{
		return (&x)[i];
	}

	template<typename T>
	const T& Vector3<T>::operator[](const uint32_t i) const
	{
		return (&x)[i];
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator=(const Vector3<T>& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(T s)
	{
		x += s; y += s; z += z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator-=(T s)
	{
		x -= s; y -= s; z -= z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(T s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(T s)
	{
		x /= s; y /= s; z /= z;
		return *this;
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}

	template<typename T>
	Vector3<T> operator-(const Vector3<T>& v)
	{
		return Vector3<T>(-v.x, -v.y, -v.z);
	}

	template<typename T>
	Vector3<T> operator+(T s, const Vector3<T>& v)
	{
		return Vector3<T>(s + v.x, s + v.y, s + v.z);
	}

	template<typename T>
	Vector3<T> operator+(const Vector3<T>& v, T s)
	{
		return Vector3<T>(v.x + s, v.y + s, v.z + s);
	}

	template<typename T>
	Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	template<typename T>
	Vector3<T> operator-(T s, const Vector3<T>& v)
	{
		return Vector3<T>(s - v.x, s - v.y, s - v.z);
	}

	template<typename T>
	Vector3<T> operator-(const Vector3<T>& v, T s)
	{
		return Vector3<T>(v.x - s, v.y - s, v.z - s);
	}

	template<typename T>
	Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	template<typename T>
	Vector3<T> operator*(T s, const Vector3<T>& v)
	{
		return Vector3<T>(s * v.x, s * v.y, s * v.z);
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& v, T s)
	{
		return Vector3<T>(v.x * s, v.y * s, v.z * s);
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	template<typename T>
	Vector3<T> operator/(T s, const Vector3<T>& v)
	{
		return Vector3<T>(s / v.x, s / v.y, s / v.z);
	}

	template<typename T>
	Vector3<T> operator/(const Vector3<T>& v, T s)
	{
		return Vector3<T>(v.x / s, v.y / s, v.z / s);
	}

	template<typename T>
	Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	}

	template<typename T>
	T dot(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template<typename T>
	Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(
			v1.y * v2.z - v2.y * v1.z,
			v1.z * v2.x - v2.z * v1.x,
			v1.x * v2.y - v2.x * v1.y);
	}

	template<typename T> inline T length(const Vector3<T>& v)
	{
		return sqrt(dot(v, v));
	}

	template<typename T> inline T distance(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return length(v2 - v1);
	}

	template<typename T> inline Vector3<T> normalize(const Vector3<T>& v)
	{
		return v / length(v);
	}

	template<typename T> inline Vector3<T> normalize(const Vector3<T>& v1, T& len)
	{
        len = length(v1);
        return v1 / len;
	}

	template<typename T> inline Vector3<T> mix(const Vector3<T>& v1, const Vector3<T>& v2, T s)
	{
		return v1 + (v2 - v1) * s;
	}

	template<typename T> inline Vector3<T> min(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return Vector3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
	}

	template<typename T> inline Vector3<T> max(const Vector3<T>& v1, const Vector3<T>& v2)
	{
        return Vector3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
    }


	////////////////////////////////////////////////////////////////

	template<typename T>
	Vector4<T>::Vector4()
	{
	}

	template<typename T>
	Vector4<T>::Vector4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}

	template<typename T>
	Vector4<T>::Vector4(const T* v) : x(v[0]), y(v[1]), z(v[2]), w(v[3])
	{
	}

	template<typename T>
	Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
	{
	}

	template<typename T>
	Vector4<T>::Vector4(const Vector3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w)
	{

	}

	template<typename T>
	T& Vector4<T>::operator[](const uint32_t i)
	{
		return (&x)[i];
	}

	template<typename T>
	const T& Vector4<T>::operator[](const uint32_t i) const
	{
		return (&x)[i];
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator=(const Vector4<T>& v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator+=(T s)
	{
		x += s; y += s; z += s; w += s;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& v)
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator-=(T s)
	{
		x -= s; y -= s; z -= s; w -= s;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& v)
	{
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator*=(T s)
	{
		x *= s; y *= s; z *= s; w *= s;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& v)
	{
		x *= v.x; y *= v.y; z *= v.z; w *= v.w;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator/=(T s)
	{
		x /= s; y /= s; z /= s; w /= s;
		return *this;
	}

	template<typename T>
	Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& v)
	{
		x /= v.x; y /= v.y; z /= v.z; w /= v.w;
		return *this;
	}

	template<typename T>
	Vector4<T> operator-(const Vector4<T>& v)
	{
		return Vector4<T>(-v.x, -v.y, -v.z, -v.w);
	}

	template<typename T>
	Vector4<T> operator+(T s, const Vector4<T>& v)
	{
		return Vector4<T>(s + v.x, s + v.y, s + v.z, s + v.w);
	}

	template<typename T>
	Vector4<T> operator+(const Vector4<T>& v, T s)
	{
		return Vector4<T>(v.x + s, v.y + s, v.z + s, v.w + s);
	}

	template<typename T>
	Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	template<typename T>
	Vector4<T> operator-(T s, const Vector4<T>& v)
	{
		return Vector4<T>(s - v.x, s - v.y, s - v.z, s - v.w);
	}

	template<typename T>
	Vector4<T> operator-(const Vector4<T>& v, T s)
	{
		return Vector4<T>(v.x - s, v.y - s, v.z - s, v.w - s);
	}

	template<typename T>
	Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	template<typename T>
	Vector4<T> operator*(T s, const Vector4<T>& v)
	{
		return Vector4<T>(s * v.x, s * v.y, s * v.z, s * v.w);
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& v, T s)
	{
		return Vector4<T>(v.x * s, v.y * s, v.z * s, v.w * s);
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
	}

	template<typename T>
	Vector4<T> operator/(T s, const Vector4<T>& v)
	{
		return Vector4<T>(s / v.x, s / v.y, s / v.z, s / v.w);
	}

	template<typename T>
	Vector4<T> operator/(const Vector4<T>& v, T s)
	{
		return Vector4<T>(v.x / s, v.y / s, v.z / s, v.wz / s);
	}

	template<typename T>
	Vector4<T> operator/(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
	}

	template<typename T>
	T dot(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template<typename T> T length(const Vector4<T>& v)
	{
		return sqrt(dot(v, v));
	}

	template<typename T> T distance(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return length(v2 - v1);
	}

	template<typename T> Vector4<T> normalize(const Vector4<T>& v)
	{
		return v / length(v);
	}

	template<typename T> Vector4<T> normalize(const Vector4<T>& v1, T& len)
	{
		len = length(v1);
		return v1 / len;
	}

	template<typename T> inline Vector4<T> min(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z), min(v1.w, v2.w));
	}

	template<typename T> inline Vector4<T> max(const Vector4<T>& v1, const Vector4<T>& v2)
	{
		return Vector4<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z), max(v1.w, v2.w));
	}
}
