#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector2 {

	public:

		union {
			MathType m_Data[2];
			struct { MathType X, Y; };
		};

		FORCEINLINE TVector2(MathType X, MathType Y);
		FORCEINLINE TVector2(MathType Scalar);
		FORCEINLINE TVector2();
		FORCEINLINE TVector2(const TVector2<MathType>& Other);

		FORCEINLINE ~TVector2();

		FORCEINLINE TVector2<MathType>& Add(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& Subtract(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& Multiply(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& Divide(const TVector2<MathType>& Other);

		FORCEINLINE friend TVector2<MathType> operator+(TVector2<MathType> Left, const TVector2<MathType>& Right);
		FORCEINLINE friend TVector2<MathType> operator-(TVector2<MathType> Left, const TVector2<MathType>& Right);
		FORCEINLINE friend TVector2<MathType> operator*(TVector2<MathType> Left, const TVector2<MathType>& Right);
		FORCEINLINE friend TVector2<MathType> operator/(TVector2<MathType> Left, const TVector2<MathType>& Right);

		FORCEINLINE TVector2<MathType>& operator+=(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& operator-=(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& operator*=(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& operator/=(const TVector2<MathType>& Other);

		FORCEINLINE bool operator==(const TVector2<MathType>& Other);
		FORCEINLINE bool operator!=(const TVector2<MathType>& Other);

		FORCEINLINE void operator++();
		FORCEINLINE void operator--();

		FORCEINLINE TVector2<MathType>& operator++(int);
		FORCEINLINE TVector2<MathType>& operator--(int) { TVector2<MathType> T = *this; --*this; return T; }

		FORCEINLINE MathType operator[](size_t Index);

		FORCEINLINE MathType Length();
		FORCEINLINE TVector2<MathType>& Normalize();
		FORCEINLINE MathType Dot(const TVector2<MathType>& Other);
		FORCEINLINE TVector2<MathType>& Rotate(MathType Angle);

	};

	template<class MathType>
	using TVec2 = TVector2<MathType>;

	using Vec2 = TVec2<MATH_TYPE>;
	using Vector2 = Vec2;

} }

#include "Vector2.inl"