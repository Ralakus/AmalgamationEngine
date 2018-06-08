#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	class TVector2 {

	public:

		union {
			T Value[2];
			struct { T X, Y; };
		};

		FORCEINLINE TVector2(T X, T Y);
		FORCEINLINE TVector2(T Scalar);
		FORCEINLINE TVector2();
		FORCEINLINE TVector2(const TVector2<T>& Other);

		FORCEINLINE ~TVector2();

		FORCEINLINE TVector2<T>& operator+=(const TVector2<T>& Other);
		FORCEINLINE TVector2<T>& operator-=(const TVector2<T>& Other);
		FORCEINLINE TVector2<T>& operator*=(const TVector2<T>& Other);
		FORCEINLINE TVector2<T>& operator/=(const TVector2<T>& Other);

		FORCEINLINE bool operator==(const TVector2<T>& Other);
		FORCEINLINE bool operator!=(const TVector2<T>& Other);

		FORCEINLINE void operator++();
		FORCEINLINE void operator--();

		FORCEINLINE TVector2<T>& operator++(int);
		FORCEINLINE TVector2<T>& operator--(int);

		FORCEINLINE T& operator[](size_t Index);
		FORCEINLINE const T& operator[](size_t Index) const;

	};

	template<class T>
	FORCEINLINE TVector2<T> operator+(TVector2<T> Left, const TVector2<T>& Right);

	template<class T>
	FORCEINLINE TVector2<T> operator-(TVector2<T> Left, const TVector2<T>& Right);

	template<class T>
	FORCEINLINE TVector2<T> operator*(TVector2<T> Left, const TVector2<T>& Right);

	template<class T>
	FORCEINLINE TVector2<T> operator/(TVector2<T> Left, const TVector2<T>& Right);

	template<class T>
	FORCEINLINE T Length(const TVector2<T>& Vec);

	template<class T>
	FORCEINLINE TVector2<T> Normalize(const TVector2<T>& Vec);

	template<class T>
	FORCEINLINE T Dot(const TVector2<T>& Vec1, const TVector2<T>& Vec2);

	template<class T>
	FORCEINLINE TVector2<T>& Rotate(const TVector2<T>& Vec, T Angle);

	template<class T>
	using TVec2 = TVector2<T>;

	using Vec2 = TVec2<MATH_TYPE>;
	using Vector2 = Vec2;

} }

#include "Vector2.inl"