#pragma once

#include "Math.hpp"

// TODO : Constexpr Sqrt => GetLength, SetLength, Normalize, Normalized, SetPolarAngle

namespace en
{

template <typename T>
class Vector2
{
public:
	static constexpr int Dim = 2;

	constexpr Vector2() : x(T(0)), y(T(0)) {}
	constexpr Vector2(const Vector2<T>& v) : x(v.x), y(v.y) {}
	template <typename U>
	constexpr Vector2(const Vector2<U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}
	constexpr Vector2(const T& s) : x(s), y(s) {}
	constexpr Vector2(const T& s1, const T& s2) : x(s1), y(s2) {}
	~Vector2() = default;

	constexpr Vector2<T>& Set(const Vector2<T> & v) { x = v.x; y = v.y; return *this; }
	template <typename U>
	constexpr Vector2<T>& Set(const Vector2<U> & v) { x = static_cast<T>(v.x); y = static_cast<T>(v.y); return *this; }
	constexpr Vector2<T>& Set(const T & s) { x = s; y = s; return *this; }
	constexpr Vector2<T>& Set(const T * a) { x = a[0]; y = a[1]; return *this; }
	constexpr Vector2<T>& Set(const T & s1, const T & s2) { x = s1; y = s2; return *this; }

	constexpr T& operator()(unsigned int i) { if (i == 0) return x; return y; }
	constexpr const T& operator()(unsigned int i) const { if (i == 0) return x; return y; }
	constexpr T& operator[](unsigned int i) { if (i == 0) return x; return y; }
	constexpr const T& operator[](unsigned int i) const { if (i == 0) return x; return y; }

	constexpr Vector2<T>& operator=(const Vector2<T> & vec) { x = vec.x; y = vec.y; return *this; }
	constexpr const Vector2<T>& operator+() const { return *this; }
	constexpr Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

	constexpr Vector2<T> operator+(const Vector2<T> & vec) const { return Vector2<T>(x + vec.x, y + vec.y); }
	constexpr Vector2<T> operator-(const Vector2<T> & vec) const { return Vector2<T>(x - vec.x, y - vec.y); }
	constexpr Vector2<T> operator*(const Vector2<T> & vec) const { return Vector2<T>(x * vec.x, y * vec.y); }
	constexpr Vector2<T> operator/(const Vector2<T> & vec) const { return Vector2<T>(x / vec.x, y / vec.y); }
	constexpr Vector2<T>& operator+=(const Vector2<T> & vec) { x += vec.x; y += vec.y; return *this; }
	constexpr Vector2<T>& operator-=(const Vector2<T> & vec) { x -= vec.x; y -= vec.y; return *this; }
	constexpr Vector2<T>& operator*=(const Vector2<T> & vec) { x *= vec.x; y *= vec.y; return *this; }
	constexpr Vector2<T>& operator/=(const Vector2<T> & vec) { x /= vec.x; y /= vec.y; return *this; }

	constexpr Vector2<T> operator+(T scalar) const { return Vector2<T>(x + scalar, y + scalar); }
	constexpr Vector2<T> operator-(T scalar) const { return Vector2<T>(x - scalar, y - scalar); }
	constexpr Vector2<T> operator*(T scalar) const { return Vector2<T>(x * scalar, y * scalar); }
	constexpr Vector2<T> operator/(T scalar) const { const T inv = T(1) / scalar; return Vector2<T>(x * inv, y * inv); }
	constexpr Vector2<T>& operator+=(T scalar) { x += scalar; y += scalar; return *this; }
	constexpr Vector2<T>& operator-=(T scalar) { x -= scalar; y -= scalar; return *this; }
	constexpr Vector2<T>& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }
	constexpr Vector2<T>& operator/=(T scalar) { const T inv = T(1) / scalar; x *= inv; y *= inv; return *this; }

	constexpr bool IsZero() const { return operator==(Zero()); }
	constexpr bool operator==(const Vector2<T> & vec) const { return Math::Equals(x, vec.x) && Math::Equals(y, vec.y); }
	constexpr bool operator!=(const Vector2<T> & vec) const { return !operator==(vec); }
	constexpr bool operator<(const Vector2<T> & vec) const { return x < vec.x&& y < vec.y; }
	constexpr bool operator<=(const Vector2<T> & vec) const { return x <= vec.x && y <= vec.y; }
	constexpr bool operator>(const Vector2<T> & vec) const { return !operator<=(vec); }
	constexpr bool operator>=(const Vector2<T> & vec) const { return !operator<(vec); }
	static constexpr bool Equals(const Vector2<T> & v1, const Vector2<T> & v2, const T & epsilon = T(Math::Epsilon)) { return Math::Equals(v1.x, v2.x, epsilon) && Math::Equals(v1.y, v2.y, epsilon); }

	constexpr T DotProduct(const Vector2<T> & v) const { return x * v.x + y * v.y; }
	static constexpr T DotProduct(const Vector2<T> & v1, const Vector2<T> & v2) { return v1.x * v2.x + v1.y * v2.y; }

	constexpr T GetSquaredLength() const { return DotProduct(*this); }
	inline T GetLength() const { return Math::FastSqrt(GetSquaredLength()); }
	inline Vector2<T>& SetLength(const T & length, T * oldLength = nullptr)
	{
		const T currentLength = GetLength();
		if (oldLength != nullptr)
		{
			*oldLength = currentLength;
		}
		const T factor = length / currentLength;
		x *= factor;
		y *= factor;
		return *this;
	}

	constexpr bool IsNormalized() const { return Math::Equals(GetSquaredLength(), T(1)); }
	inline Vector2<T>& Normalize(T * oldLength = nullptr) { return SetLength(T(1), oldLength); }
	inline Vector2<T> Normalized(T * oldLength = nullptr) const { return Vector2<T>(*this).Normalize(oldLength); }

	constexpr T GetPolarAngle() const { return Math::Atan2(x, y); }
	inline Vector2<T>& SetPolarAngle(const T & angle)
	{
		const T length = GetLength();
		x = Math::Cos(angle) * length;
		y = Math::Sin(angle) * length;
		return *this;
	}
	static constexpr Vector2<T> Polar(const T & angle, const T & length = T(1)) { return Vector2<T>(Math::Cos(angle) * length, Math::Sin(angle) * length); }

	constexpr Vector2<T>& Rotate(const T & angle)
	{
		const T c = Math::Cos(angle);
		const T s = Math::Sin(angle);
		const T tx = c * x - s * y;
		y = s * x + c * y;
		x = tx;
		return *this;
	}
	constexpr Vector2<T> Rotated(const T & angle) const
	{
		const T c = Math::Cos(angle);
		const T s = Math::Sin(angle);
		return Vector2<T>(c * x - s * y, s * x + c * y);
	}

	static constexpr Vector2<T> Lerp(const Vector2<T> & v1, const Vector2<T> & v2, const T & percent) { const T one_minus_percent = T(1) - percent; return Vector2<T>(one_minus_percent * v1.x + percent * v2.x, one_minus_percent * v1.y + percent * v2.y); }

	constexpr Vector2<T>& Maximize(const Vector2<T> & v) { if (v.x > x) x = v.x; if (v.y > y) y = v.y; return *this; }
	static constexpr Vector2<T> Maximum(const Vector2<T> & v1, const Vector2<T> & v2) { return Vector2<T>(Math::Max(v1.x, v2.x), Math::Max(v1.y, v2.y)); }

	constexpr Vector2<T>& Minimize(const Vector2<T> & v) { if (v.x < x) x = v.x; if (v.y < y) y = v.y; return *this; }
	static constexpr Vector2<T> Minimum(const Vector2<T> & v1, const Vector2<T> & v2) { return Vector2<T>(Math::Min(v1.x, v2.x), Math::Min(v1.y, v2.y)); }

	static constexpr Vector2<T> Unit() { return Vector2<T>(1, 1); }
	static constexpr Vector2<T> UnitX() { return Vector2<T>(1, 0); }
	static constexpr Vector2<T> UnitY() { return Vector2<T>(0, 1); }
	static constexpr Vector2<T> Zero() { return Vector2<T>(0, 0); }

	T x;
	T y;
};

template <typename T> constexpr Vector2<T> operator+(const T& scalar, const Vector2<T>& vector) { return vector + scalar; }
template <typename T> constexpr Vector2<T> operator-(const T& scalar, const Vector2<T>& vector) { return scalar + (-vector); }
template <typename T> constexpr Vector2<T> operator*(const T& scalar, const Vector2<T>& vector) { return vector * scalar; }
template <typename T> constexpr Vector2<T> operator/(const T& scalar, const Vector2<T>& vector) { return Vector2<T>(scalar / vector.x, scalar / vector.y); }

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;

typedef Vector2f vec2; // GLSL-like

} // namespace en
