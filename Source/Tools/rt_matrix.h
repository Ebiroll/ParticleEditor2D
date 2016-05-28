#pragma once

#include "rt_vector.h"

namespace vis
{
	template<typename T> struct Matrix33;
	template<typename T> struct Matrix44;

	////////////////////////////////////////////////////////////////

	template<typename T>
	struct Matrix33
	{
		Vector3<T> m[3];

		Matrix33();
		Matrix33(const Matrix33<T>& m);

		explicit Matrix33(T x);
		explicit Matrix33(const T* m);
		explicit Matrix33(const Vector3<T>& c0, const Vector3<T>& c1, const Vector3<T>& c2);
		explicit Matrix33(
			T const & x0, T const & y0, T const & z0,
			T const & x1, T const & y1, T const & z1,
			T const & x2, T const & y2, T const & z2);

		explicit Matrix33(const Matrix44<T>& m);

		Vector3<T>& operator[](const uint32_t i);
		const Vector3<T>& operator[](const uint32_t i) const;

		Matrix33<T>& operator=(const Matrix33<T>& m);

		Matrix33<T>& operator+=(const T& s);
		Matrix33<T>& operator+=(const Matrix33<T>& m);
		Matrix33<T>& operator-=(const T& s);
		Matrix33<T>& operator-=(const Matrix33<T>& m);
		Matrix33<T>& operator*=(const T& s);
		Matrix33<T>& operator*=(const Matrix33<T>& m);
		Matrix33<T>& operator/=(const T& s);
		Matrix33<T>& operator/=(const Matrix33<T>& m);

		static const Matrix33<T> identity;
	};

    typedef Matrix33<float> Matrix33_f ;

	template<typename T> Matrix33<T> operator-(const Matrix33<T>& m);

	template<typename T> Matrix33<T> operator+(const T& s, const Matrix33<T>& m);
	template<typename T> Matrix33<T> operator+(const Matrix33<T>& m, const T& s);
	template<typename T> Matrix33<T> operator+(const Matrix33<T>& m1, const Matrix33<T>& m2);
	template<typename T> Matrix33<T> operator-(const T& s, const Matrix33<T>& m);
	template<typename T> Matrix33<T> operator-(const Matrix33<T>& m, const T& s);
	template<typename T> Matrix33<T> operator-(const Matrix33<T>& m1, const Matrix33<T>& m2);
	template<typename T> Matrix33<T> operator*(const T& s, const Matrix33<T>& m);
	template<typename T> Matrix33<T> operator*(const Matrix33<T>& m, const T& s);
	template<typename T> Vector3<T> operator*(const Vector3<T>& v, const Matrix33<T>& m);
	template<typename T> Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v);
	template<typename T> Matrix33<T> operator*(const Matrix33<T>& m1, const Matrix33<T>& m2);
	template<typename T> Matrix33<T> operator/(const T& s, const Matrix33<T>& m);
	template<typename T> Matrix33<T> operator/(const Matrix33<T>& m, const T& s);
	template<typename T> Matrix33<T> operator/(const Vector3<T>& v, const Matrix33<T>& m);
	template<typename T> Matrix33<T> operator/(const Matrix33<T>& m, const Vector3<T>& v);
	template<typename T> Matrix33<T> operator/(const Matrix33<T>& m1, const Matrix33<T>& m2);

	template <typename T> Matrix33<T> identity3();
	template <typename T> Matrix33<T> transpose(const Matrix33<T>& m);
	template <typename T> Matrix33<T> inverse(const Matrix33<T>& m);
	template <typename T> Matrix33<T> affine_inverse(const Matrix33<T>& m);

	////////////////////////////////////////////////////////////////

	template<typename T>
	struct Matrix44
	{
		Vector4<T> m[4];

		Matrix44();
		Matrix44(const Matrix44<T>& m);

		explicit Matrix44(T x);
		explicit Matrix44(const T* m);
		explicit Matrix44(const Vector4<T>& c0, const Vector4<T>& c1, const Vector4<T>& c2, const Vector4<T>& c3);
		explicit Matrix44(
			T const & x0, T const & y0, T const & z0, T const & w0,
			T const & x1, T const & y1, T const & z1, T const & w1,
			T const & x2, T const & y2, T const & z2, T const & w2,
			T const & x3, T const & y3, T const & z3, T const & w3);

		explicit Matrix44(const Matrix33<T>& m);

		Vector4<T>& operator[](const uint32_t i);
		const Vector4<T>& operator[](const uint32_t i) const;

		Matrix44<T>& operator=(const Matrix44<T>& m);

		Matrix44<T>& operator+=(const T& s);
		Matrix44<T>& operator+=(const Matrix44<T>& m);
		Matrix44<T>& operator-=(const T& s);
		Matrix44<T>& operator-=(const Matrix44<T>& m);
		Matrix44<T>& operator*=(const T& s);
		Matrix44<T>& operator*=(const Matrix44<T>& m);
		Matrix44<T>& operator/=(const T& s);
		Matrix44<T>& operator/=(const Matrix44<T>& m);

		static const Matrix44<T> identity;
	};

    typedef Matrix44<float> Matrix44_f;

	template<typename T> Matrix44<T> operator-(const Matrix44<T>& m);

	template<typename T> Matrix44<T> operator+(const T& s, const Matrix44<T>& m);
	template<typename T> Matrix44<T> operator+(const Matrix44<T>& m, const T& s);
	template<typename T> Matrix44<T> operator+(const Matrix44<T>& m1, const Matrix44<T>& m2);
	template<typename T> Matrix44<T> operator-(const T& s, const Matrix44<T>& m);
	template<typename T> Matrix44<T> operator-(const Matrix44<T>& m, const T& s);
	template<typename T> Matrix44<T> operator-(const Matrix44<T>& m1, const Matrix44<T>& m2);
	template<typename T> Matrix44<T> operator*(const T& s, const Matrix44<T>& m);
	template<typename T> Matrix44<T> operator*(const Matrix44<T>& m, const T& s);
	template<typename T> Vector4<T> operator*(const Vector4<T>& v, const Matrix44<T>& m);
	template<typename T> Vector4<T> operator*(const Matrix44<T>& m, const Vector4<T>& v);
	template<typename T> Matrix44<T> operator*(const Matrix44<T>& m1, const Matrix44<T>& m2);
	template<typename T> Matrix44<T> operator/(const T& s, const Matrix44<T>& m);
	template<typename T> Matrix44<T> operator/(const Matrix44<T>& m, const T& s);
	template<typename T> Vector4<T> operator/(const Vector4<T>& v, const Matrix44<T>& m);
	template<typename T> Vector4<T> operator/(const Matrix44<T>& m, const Vector4<T>& v);
	template<typename T> Matrix44<T> operator/(const Matrix44<T>& m1, const Matrix44<T>& m2);

	template <typename T> Matrix44<T> transpose(const Matrix44<T>& m);
	template <typename T> Matrix44<T> inverse(const Matrix44<T>& m);
	template <typename T> Matrix44<T> affine_inverse(const Matrix44<T>& m);
	template <typename T> Matrix44<T> translation(const Vector3<T>& v);
	template <typename T> Matrix44<T> rotation(T a, const Vector3<T>& v);
	template <typename T> Matrix44<T> scaling(const Vector3<T>& v);
	template <typename T> Matrix44<T> ortho(T left, T right, T bottom, T top, T near, T far);
	template <typename T> Matrix44<T> perspective(T fov, T aspect, T near, T far);
	template <typename T> Matrix44<T> infinite_perspective(T fov, T aspect, T near, T eps = 0);
	template <typename T> Matrix44<T> look_at(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up);
	template <typename T> Matrix44<T> rotation_yaw_pitch_roll(const T& yaw, const T& pitch, const T& roll);
	template <typename T> Matrix44<T> create_transform(const Matrix33<T>& rotation, const Vector3<T>& position);

	////////////////////////////////////////////////////////////////

	template<typename T>
	Matrix33<T>::Matrix33()
	{
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Matrix33<T>& m)
	{
		this->m[0] = m[0];
		this->m[1] = m[1];
		this->m[2] = m[2];
	}

	template<typename T>
	Matrix33<T>::Matrix33(T x)
	{
		this->m[0] = Vector3<T>(x, 0, 0);
		this->m[1] = Vector3<T>(0, x, 0);
		this->m[2] = Vector3<T>(0, 0, x);
	}

	template<typename T>
	Matrix33<T>::Matrix33(const T* m)
	{
		this->m[0] = Vector3<T>(&m[0]);
		this->m[1] = Vector3<T>(&m[3]);
		this->m[2] = Vector3<T>(&m[6]);
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Vector3<T>& c0, const Vector3<T>& c1, const Vector3<T>& c2)
	{
		this->m[0] = c0;
		this->m[1] = c1;
		this->m[2] = c2;
	}

	template<typename T>
	Matrix33<T>::Matrix33(
		T const & x0, T const & y0, T const & z0,
		T const & x1, T const & y1, T const & z1,
		T const & x2, T const & y2, T const & z2)
	{
		this->m[0] = Vector3<T>(x0, y0, z0);
		this->m[1] = Vector3<T>(x1, y1, z1);
		this->m[2] = Vector3<T>(x2, y2, z2);
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Matrix44<T>& m)
	{
		this->m[0] = Vector3<T>(m[0]);
		this->m[1] = Vector3<T>(m[1]);
		this->m[2] = Vector3<T>(m[2]);
	}

	template<typename T>
	Vector3<T>& Matrix33<T>::operator[](const uint32_t i)
	{
		return m[i];
	}

	template<typename T>
	const Vector3<T>& Matrix33<T>::operator[](const uint32_t i) const
	{
		return m[i];
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator=(const Matrix33<T>& m)
	{
		this->m[0] = m[0];
		this->m[1] = m[1];
		this->m[2] = m[2];
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator+=(const T& s)
	{
		m[0] += s;
		m[1] += s;
		m[2] += s;
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator+=(const Matrix33<T>& m)
	{
		this->m[0] += m[0];
		this->m[1] += m[1];
		this->m[2] += m[2];
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator-=(const T& s)
	{
		m[0] -= s;
		m[1] -= s;
		m[2] -= s;
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator-=(const Matrix33<T>& m)
	{
		this->m[0] -= m[0];
		this->m[1] -= m[1];
		this->m[2] -= m[2];
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator*=(const T& s)
	{
		m[0] *= s;
		m[1] *= s;
		m[2] *= s;
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator*=(const Matrix33<T>& m)
	{
		return (*this = *this * m);
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator/=(const T& s)
	{
		m[0] /= s;
		m[1] /= s;
		m[2] /= s;
		return *this;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator/=(const Matrix33<T>& m)
	{
		return (*this = *this / m);
	}

	template<typename T>
	Matrix33<T> operator-(const Matrix33<T>& m)
	{
		return Matrix33<T>(-m[0], -m[1], -m[2]);
	}

	template<typename T>
	Matrix33<T> operator+(const T& s, const Matrix33<T>& m)
	{
		return Matrix33<T>(s + m[0], s + m[1], s + m[2]);
	}

	template<typename T>
	Matrix33<T> operator+(const Matrix33<T>& m, const T& s)
	{
		return Matrix33<T>( m[0] + s, m[1] + s, m[2] + s);
	}

	template<typename T>
	Matrix33<T> operator+(const Matrix33<T>& m1, const Matrix33<T>& m2)
	{
		return Matrix33<T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]);
	}

	template<typename T>
	Matrix33<T> operator-(const T& s, const Matrix33<T>& m)
	{
		return Matrix33<T>(s - m[0], s - m[1], s - m[2]);
	}

	template<typename T>
	Matrix33<T> operator-(const Matrix33<T>& m, const T& s)
	{
		return Matrix33<T>(m[0] - s, m[1] - s, m[2] - s);
	}

	template<typename T>
	Matrix33<T> operator-(const Matrix33<T>& m1, const Matrix33<T>& m2)
	{
		return Matrix33<T>(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]);
	}

	template<typename T>
	Matrix33<T> operator*(const T& s, const Matrix33<T>& m)
	{
		return Matrix33<T>(s * m[0], s * m[1], s * m[2]);
	}

	template<typename T>
	Matrix33<T> operator*(const Matrix33<T>& m, const T& s)
	{
		return Matrix33<T>(m[0] * s, m[1] * s, m[2] * s);
	}
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& v, const Matrix33<T>& m)
	{
		// [1x3]*[3x3]
		return Vector3<T>(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]);
	}

	template<typename T>
	Vector3<T> operator*(const Matrix33<T>& m, const Vector3<T>& v)
	{
		// [3x3]*[3x1]
		return Vector3<T>(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]);
	}

	template<typename T>
	Matrix33<T> operator*(const Matrix33<T>& m1, const Matrix33<T>& m2)
	{
		// [3x3]*[3x3]
		Vector3<T> a0 = m1[0]; Vector3<T> b0 = m2[0];
		Vector3<T> a1 = m1[1];	Vector3<T> b1 = m2[1];
		Vector3<T> a2 = m1[2];	Vector3<T> b2 = m2[2];

		Matrix33<T> tmp;
		tmp[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2];
		tmp[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2];
		tmp[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2];
		return tmp;
	}

	template<typename T>
	Matrix33<T> operator/(const T& s, const Matrix33<T>& m)
	{
		return Matrix33<T>(s / m[0], s / m[1], s / m[2]);
	}

	template<typename T>
	Matrix33<T> operator/(const Matrix33<T>& m, const T& s)
	{
		return Matrix33<T>(m[0] / s, m[1] / s, m[2] / s);
	}

	template<typename T>
	Matrix33<T> operator/(const Vector3<T>& v, const Matrix33<T>& m)
	{
		return v * inverse(m);

	}

	template<typename T>
	Matrix33<T> operator/(const Matrix33<T>& m, const Vector3<T>& v)
	{
		return inverse(m) * v;
	}

	template<typename T>
	Matrix33<T> operator/(const Matrix33<T>& m1, const Matrix33<T>& mv2)
	{
		return m1 * inverse(mv2);
	}

	template <typename T>
	Matrix33<T> transpose(const Matrix33<T>& m)
	{
		Matrix33<T> tmp;
		tmp[0][0] = m[0][0]; tmp[1][0] = m[0][1]; tmp[2][0] = m[0][2];
		tmp[0][1] = m[1][0]; tmp[1][1] = m[1][1]; tmp[2][1] = m[1][2];
		tmp[0][2] = m[2][0]; tmp[1][2] = m[2][1]; tmp[2][2] = m[2][2];
		return tmp;
	}

	template <typename T>
	Matrix33<T> inverse(const Matrix33<T>& m)
	{
		T s00 = m[0][0];
		T s01 = m[0][1];
		T s02 = m[0][2];

		T s10 = m[1][0];
		T s11 = m[1][1];
		T s12 = m[1][2];

		T s20 = m[2][0];
		T s21 = m[2][1];
		T s22 = m[2][2];
		
		Matrix33<T> tmp(
			s11 * s22 - s21 * s12,
			s12 * s20 - s22 * s10,
			s10 * s21 - s20 * s11,
			s02 * s21 - s01 * s22,
			s00 * s22 - s02 * s20,
			s01 * s20 - s00 * s21,
			s12 * s01 - s11 * s02,
			s10 * s02 - s12 * s00,
			s11 * s00 - s10 * s01);

		T det = s00 * (s11 * s22 - s21 * s12)
			  - s10 * (s01 * s22 - s21 * s02)
			  + s20 * (s01 * s12 - s11 * s02);

		tmp /= det;
		return tmp;
	}


	template <typename T>
	Matrix33<T> affine_inverse(const Matrix33<T>& m)
	{
		return transpose(m);
	}

	template <typename T>
	const Matrix33<T> Matrix33<T>::identity(1);

	////////////////////////////////////////////////////////////////
	template<typename T>
	Matrix44<T>::Matrix44()
	{
	}

	template<typename T>
	Matrix44<T>::Matrix44(const Matrix44<T>& m)
	{
		this->m[0] = m[0];
		this->m[1] = m[1];
		this->m[2] = m[2];
		this->m[3] = m[3];
	}

	template<typename T>
	Matrix44<T>::Matrix44(T x)
	{
		this->m[0] = Vector4<T>(x, 0, 0, 0);
		this->m[1] = Vector4<T>(0, x, 0, 0);
		this->m[2] = Vector4<T>(0, 0, x, 0);
		this->m[3] = Vector4<T>(0, 0, 0, x);
	}

	template<typename T>
	Matrix44<T>::Matrix44(const T* m)
	{
		this->m[0] = Vector4<T>(&m[ 0]);
		this->m[1] = Vector4<T>(&m[ 4]);
		this->m[2] = Vector4<T>(&m[ 8]);
		this->m[3] = Vector4<T>(&m[12]);
	}

	template<typename T>
	Matrix44<T>::Matrix44(const Vector4<T>& c0, const Vector4<T>& c1, const Vector4<T>& c2, const Vector4<T>& c3)
	{
		this->m[0] = c0;
		this->m[1] = c1;
		this->m[2] = c2;
		this->m[3] = c3;
	}

	template<typename T>
	Matrix44<T>::Matrix44(
		T const & x0, T const & y0, T const & z0, T const & w0,
		T const & x1, T const & y1, T const & z1, T const & w1,
		T const & x2, T const & y2, T const & z2, T const & w2,
		T const & x3, T const & y3, T const & z3, T const & w3)
	{
		this->m[0] = Vector4<T>(x0, y0, z0, w0);
		this->m[1] = Vector4<T>(x1, y1, z1, w1);
		this->m[2] = Vector4<T>(x2, y2, z2, w2);
		this->m[3] = Vector4<T>(x3, y3, z3, w3);
	}

	template<typename T>
	Matrix44<T>::Matrix44(const Matrix33<T>& m)
	{
		this->m[0] = Vector4<T>(m[0], 0);
		this->m[1] = Vector4<T>(m[1], 0);
		this->m[2] = Vector4<T>(m[2], 0);
		this->m[3] = Vector4<T>(0, 0, 0, 1);
	}


	template<typename T>
	Vector4<T>& Matrix44<T>::operator[](const uint32_t i)
	{
		return m[i];
	}

	template<typename T>
	const Vector4<T>& Matrix44<T>::operator[](const uint32_t i) const
	{
		return m[i];
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T>& m)
	{
		this->m[0] = m[0];
		this->m[1] = m[1];
		this->m[2] = m[2];
		this->m[3] = m[3];
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator+=(const T& s)
	{
		m[0] += s;
		m[1] += s;
		m[2] += s;
		m[3] += s;
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator+=(const Matrix44<T>& m)
	{
		this->m[0] += m[0];
		this->m[1] += m[1];
		this->m[2] += m[2];
		this->m[3] += m[3];
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator-=(const T& s)
	{
		m[0] -= s;
		m[1] -= s;
		m[2] -= s;
		m[3] -= s;
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator-=(const Matrix44<T>& m)
	{
		this->m[0] -= m[0];
		this->m[1] -= m[1];
		this->m[2] -= m[2];
		this->m[3] -= m[3];
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator*=(const T& s)
	{
		m[0] *= s;
		m[1] *= s;
		m[2] *= s;
		m[3] *= s;
		return *this;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator*=(const Matrix44<T>& m)
	{
		return (*this = *this * m);
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator/=(const T& s)
	{
		m[0] /= s;
		m[1] /= s;
		m[2] /= s;
		m[3] /= s;
		return *this;
	}

	template<typename T>
	inline Matrix44<T>& Matrix44<T>::operator/=(const Matrix44<T>& m)
	{
		return (*this = *this / m);
	}

	template<typename T>
	inline Matrix44<T> operator-(const Matrix44<T>& mv)
	{
		return Matrix44<T>(
            -mv[0],
            -mv[1],
            -mv[2],
            -mv[3]);
	}

	template<typename T>
	inline Matrix44<T> operator+(const T& s, const Matrix44<T>& m)
	{
		return Matrix44<T>(
			s + m[0],
			s + m[1],
			s + m[2],
			s + m[3]);
	}

	template<typename T>
	inline Matrix44<T> operator+(const Matrix44<T>& m, const T& s)
	{
		return Matrix44<T>(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	template<typename T>
	inline Matrix44<T> operator+(const Matrix44<T>& m1, const Matrix44<T>& m2)
	{
		return Matrix44<T>(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}

	template<typename T>
	inline Matrix44<T> operator-(const T& s, const Matrix44<T>& m)
	{
		return Matrix44<T>(
			s - m[0],
			s - m[1],
			s - m[2],
			s - m[3]);
	}

	template<typename T>
	inline Matrix44<T> operator-(const Matrix44<T>& m, const T& s)
	{
		return Matrix44<T>(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s);
	}

	template<typename T>
	inline Matrix44<T> operator-(const Matrix44<T>& m1, const Matrix44<T>& m2)
	{
		return Matrix44<T>(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	template<typename T>
	inline Matrix44<T> operator*(const T& s, const Matrix44<T>& m)
	{
		return Matrix44<T>(
			s * m[0],
			s * m[1],
			s * m[2],
			s * m[3]);
	}

	template<typename T>
	inline Matrix44<T> operator*(const Matrix44<T>& m, const T& s)
	{
		return Matrix44<T>(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}
	template<typename T>
	inline Vector4<T> operator*(const Vector4<T>& v, const Matrix44<T>& m)
	{
		// [1x4]*[4x4]
		return Vector4<T>(
			v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
			v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
			v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
			v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]);
	}

	template<typename T>
	inline Vector4<T> operator*(const Matrix44<T>& m, const Vector4<T>& v)
	{
		// [4x4]*[4x1]
		return Vector4<T>(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
			m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]);
	}

	template<typename T>
	inline Matrix44<T> operator*(const Matrix44<T>& m1, const Matrix44<T>& m2)
	{
		// [4x4]*[4x4]
		return Matrix44<T>(
			m1 * m2[0],
			m1 * m2[1],
			m1 * m2[2],
			m1 * m2[3]);
	}

	template<typename T>
	inline Matrix44<T> operator/(const T& s, const Matrix44<T>& m)
	{
		return Matrix44<T>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	template<typename T>
	inline Matrix44<T> operator/(const Matrix44<T>& m, const T& s)
	{
		return Matrix44<T>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	template<typename T>
	inline Vector4<T> operator/(const Vector4<T>& v, const Matrix44<T>& m)
	{
		return v * inverse(m);
		
	}

	template<typename T>
	inline Vector4<T> operator/(const Matrix44<T>& m, const Vector4<T>& v)
	{
		return inverse(m) * v;
	}

	template<typename T>
	inline Matrix44<T> operator/(const Matrix44<T>& m1, const Matrix44<T>& m2)
	{
		return m1 * inverse(m2);
	}

	template <typename T>
	inline Matrix44<T> transpose(const Matrix44<T>& m)
	{
		Matrix44<T> tmp;
		tmp[0][0] = m[0][0]; tmp[1][0] = m[0][1]; tmp[2][0] = m[0][2];  tmp[3][0] = m[0][3];
		tmp[0][1] = m[1][0]; tmp[1][1] = m[1][1]; tmp[2][1] = m[1][2];	tmp[3][1] = m[1][3];
		tmp[0][2] = m[2][0]; tmp[1][2] = m[2][1]; tmp[2][2] = m[2][2];	tmp[3][2] = m[2][3];
		tmp[0][3] = m[3][0]; tmp[1][3] = m[3][1]; tmp[2][3] = m[3][2];	tmp[3][3] = m[3][3];
		return tmp;
	}

	template <typename T>
	inline Matrix44<T> inverse(const Matrix44<T>& m)
	{
		T s00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T s01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T s02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T s03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T s04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T s05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T s06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T s07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T s08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T s09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T s10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T s11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T s12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T s13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		T s14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		T s15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		T s16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
		T s17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
		T s18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Matrix44<T> tmp(
			+m[1][1] * s00 - m[1][2] * s01 + m[1][3] * s02,
			-m[1][0] * s00 + m[1][2] * s03 - m[1][3] * s04,
			+m[1][0] * s01 - m[1][1] * s03 + m[1][3] * s05,
			-m[1][0] * s02 + m[1][1] * s04 - m[1][2] * s05,

			-m[0][1] * s00 + m[0][2] * s01 - m[0][3] * s02,
			+m[0][0] * s00 - m[0][2] * s03 + m[0][3] * s04,
			-m[0][0] * s01 + m[0][1] * s03 - m[0][3] * s05,
			+m[0][0] * s02 - m[0][1] * s04 + m[0][2] * s05,

			+m[0][1] * s06 - m[0][2] * s07 + m[0][3] * s08,
			-m[0][0] * s06 + m[0][2] * s09 - m[0][3] * s10,
			+m[0][0] * s11 - m[0][1] * s09 + m[0][3] * s12,
			-m[0][0] * s08 + m[0][1] * s10 - m[0][2] * s12,

			-m[0][1] * s13 + m[0][2] * s14 - m[0][3] * s15,
			+m[0][0] * s13 - m[0][2] * s16 + m[0][3] * s17,
			-m[0][0] * s14 + m[0][1] * s16 - m[0][3] * s18,
			+m[0][0] * s15 - m[0][1] * s17 + m[0][2] * s18);

		T det =
			+m[0][0] * tmp[0][0]
			+ m[0][1] * tmp[1][0]
			+ m[0][2] * tmp[2][0]
			+ m[0][3] * tmp[3][0];

		tmp /= det;
		return tmp;
	}

	template <typename T>
	Matrix44<T> affine_inverse(const Matrix44<T>& m)
	{
		Vector4<T> v(-m[3][0], -m[3][1], -m[3][2], 1);

		Matrix44<T> tmp;
		tmp[0][0] = m[0][0]; tmp[0][1] = m[1][0]; tmp[0][2] = m[2][0]; tmp[0][3] = 0;
		tmp[1][0] = m[0][1]; tmp[1][1] = m[1][1]; tmp[1][2] = m[2][1]; tmp[1][3] = 0;
		tmp[2][0] = m[0][2]; tmp[2][1] = m[1][2]; tmp[2][2] = m[2][2]; tmp[2][3] = 0;
		tmp[3][0] = v[0] * tmp[0][0] + v[1] * tmp[1][0] + v[2] * tmp[2][0];
		tmp[3][1] = v[0] * tmp[0][1] + v[1] * tmp[1][1] + v[2] * tmp[2][1];
		tmp[3][2] = v[0] * tmp[0][2] + v[1] * tmp[1][2] + v[2] * tmp[2][2];
		tmp[3][3] = v[3];
		return tmp;
	}

	template <typename T>
	Matrix44<T> translation(const Vector3<T>& v)
	{
		Matrix44<T> tmp;
		tmp[0][0] = 1; tmp[1][0] = 0; tmp[2][0] = 0; tmp[3][0] = v[0];
		tmp[0][1] = 0; tmp[1][1] = 1; tmp[2][1] = 0; tmp[3][1] = v[1];
		tmp[0][2] = 0; tmp[1][2] = 0; tmp[2][2] = 1; tmp[3][2] = v[2];
		tmp[0][3] = 0; tmp[1][3] = 0; tmp[2][3] = 0; tmp[3][3] = 1;
		return tmp;
	}

	template <typename T>
	Matrix44<T> rotation(T a, const Vector3<T>& v)
	{
		T c = cos(a);
		T s = sin(a);

		Vector3<T> axis = normalize(v);
		Vector3<T> aa = (T(1) - c) * axis;

		Matrix44<T> tmp;
		tmp[0][0] = c + aa[0] * axis[0];
		tmp[0][1] = 0 + aa[0] * axis[1] + s * axis[2];
		tmp[0][2] = 0 + aa[0] * axis[2] - s * axis[1];
		tmp[0][3] = 0;

		tmp[1][0] = 0 + aa[1] * axis[0] - s * axis[2];
		tmp[1][1] = c + aa[1] * axis[1];
		tmp[1][2] = 0 + aa[1] * axis[2] + s * axis[0];
		tmp[1][3] = 0;

		tmp[2][0] = 0 + aa[2] * axis[0] + s * axis[1];
		tmp[2][1] = 0 + aa[2] * axis[1] - s * axis[0];
		tmp[2][2] = c + aa[2] * axis[2];
		tmp[2][3] = 0;

		tmp[3][0] = 0;
		tmp[3][1] = 0;
		tmp[3][2] = 0;
		tmp[3][3] = 1;

		return tmp;
	}

	template <typename T>
	Matrix44<T> scaling(const Vector3<T>& v)
	{
		Matrix44<T> tmp;
		tmp[0][0] = v[0]; tmp[1][0] = 0;    tmp[2][0] = 0;    tmp[3][0] = 0;
		tmp[0][1] = 0;    tmp[1][1] = v[1]; tmp[2][1] = 0;    tmp[3][1] = 0;
		tmp[0][2] = 0;    tmp[1][2] = 0;    tmp[2][2] = v[2]; tmp[3][2] = 0;
		tmp[0][3] = 0;    tmp[1][3] = 0;    tmp[2][3] = 0;    tmp[3][3] = 1;
		return tmp;
	}

	template <typename T>
    Matrix44<T> ortho(T left, T right, T bottom, T top, T nearM, T farM)
	{
		Matrix44<T> tmp;

		tmp[0][0] = T(2) / (right - left);
		tmp[0][1] = 0;
		tmp[0][2] = 0;
		tmp[0][3] = 0;

		tmp[1][0] = 0;
		tmp[1][1] = T(2) / (top - bottom);
		tmp[1][2] = 0;
		tmp[1][3] = 0;

		tmp[2][0] = 0;
		tmp[2][1] = 0;
        tmp[2][2] = -T(2) / (farM - nearM);
		tmp[2][3] = 0;

		tmp[3][0] = -(right + left) / (right - left);
		tmp[3][1] = -(top + bottom) / (top - bottom);
        tmp[3][2] = -(farM + nearM) / (farM - nearM);
		tmp[3][3] = 1;

		return tmp;
	}

	template <typename T>
    Matrix44<T> perspective(T fov, T aspect, T nearM, T farM)
	{
        T range = tan(radians(fov / T(2))) * nearM;
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		Matrix44<T> tmp;
        tmp[0][0] = (T(2) * nearM) / (right - left);
		tmp[0][1] = 0;
		tmp[0][2] = 0;
		tmp[0][3] = 0;

		tmp[1][0] = 0;
        tmp[1][1] = (T(2) * nearM) / (top - bottom);
		tmp[1][2] = 0;
		tmp[1][3] = 0;

		tmp[2][0] = 0;
		tmp[2][1] = 0;
        tmp[2][2] = -(farM + nearM) / (farM - nearM);
		tmp[2][3] = -T(1);

		tmp[3][0] = 0;
		tmp[3][1] = 0;
        tmp[3][2] = -(T(2) * farM * nearM) / (farM - nearM);
		tmp[3][3] = 0;

		return tmp;
	}

	template <typename T>
    Matrix44<T> infinite_perspective(T fov, T aspect, T nearM, T eps)
	{
        T range = tan(radians(fov / T(2))) * nearM;
		T left = -range * aspect;
		T right = range * aspect;
		T bottom = -range;
		T top = range;

		Matrix44<T> tmp;
        tmp[0][0] = (T(2) * nearM) / (right - left);
		tmp[0][1] = 0;
		tmp[0][2] = 0;
		tmp[0][3] = 0;

		tmp[1][0] = 0;
        tmp[1][1] = (T(2) * nearM) / (top - bottom);
		tmp[1][2] = 0;
		tmp[1][3] = 0;

		tmp[2][0] = 0;
		tmp[2][1] = 0;
		tmp[2][2] = eps - T(1);
		tmp[2][3] = -T(1);

		tmp[3][0] = 0;
		tmp[3][1] = 0;
        tmp[3][2] = (eps - T(2)) * nearM;
		tmp[3][3] = 0;

		return tmp;
	}

	template <typename T>
	inline Matrix44<T> look_at(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
	{
		Vector3<T> z = normalize(center - eye);
		Vector3<T> x = normalize(cross(z, up));
		Vector3<T> y = cross(x, z);

		Matrix44<T> tmp;
		tmp[0][0] =  x[0]; tmp[1][0] =  x[1]; tmp[2][0] =  x[2]; tmp[3][0] = -dot(x, eye);
		tmp[0][1] =  y[0]; tmp[1][1] =  y[1]; tmp[2][1] =  y[2]; tmp[3][1] = -dot(y, eye);
		tmp[0][2] = -z[0]; tmp[1][2] = -z[1]; tmp[2][2] = -z[2]; tmp[3][2] =  dot(z, eye);
		tmp[0][3] =  0;	   tmp[1][3] =  0;	  tmp[2][3] =  0;    tmp[3][3] =  1;
		return tmp;
	}

	template <typename T>
	inline Matrix44<T> rotation_yaw_pitch_roll(const T& yaw, const T& pitch, const T& roll)
	{
		T tmp_ch = cos(yaw);
		T tmp_sh = sin(yaw);
		T tmp_cp = cos(pitch);
		T tmp_sp = sin(pitch);
		T tmp_cb = cos(roll);
		T tmp_sb = sin(roll);

		Matrix44<T> tmp;
		tmp[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		tmp[0][1] = tmp_sb * tmp_cp;
		tmp[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		tmp[0][3] = T(0);
		tmp[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		tmp[1][1] = tmp_cb * tmp_cp;
		tmp[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		tmp[1][3] = T(0);
		tmp[2][0] = tmp_sh * tmp_cp;
		tmp[2][1] = -tmp_sp;
		tmp[2][2] = tmp_ch * tmp_cp;
		tmp[2][3] = T(0);
		tmp[3][0] = T(0);
		tmp[3][1] = T(0);
		tmp[3][2] = T(0);
		tmp[3][3] = T(1);
		return tmp;
	}

	template <typename T>
	Matrix44<T> create_transform(const Matrix33<T>& rotation, const Vector3<T>& position)
	{
		Matrix44<T> tmp;
		tmp[0][0] = rotation[0][0];
		tmp[0][1] = rotation[0][1];
		tmp[0][2] = rotation[0][2];
		tmp[0][3] = T(0);
		tmp[1][0] = rotation[1][0];
		tmp[1][1] = rotation[1][1];
		tmp[1][2] = rotation[1][2];
		tmp[1][3] = T(0);
		tmp[2][0] = rotation[2][0];
		tmp[2][1] = rotation[2][1];
		tmp[2][2] = rotation[2][2];
		tmp[2][3] = T(0);
		tmp[3][0] = position[0];
		tmp[3][1] = position[1];
		tmp[3][2] = position[2];
		tmp[3][3] = T(1);

		return tmp;
	}

	template <typename T>
	const Matrix44<T> Matrix44<T>::identity(1);
}
