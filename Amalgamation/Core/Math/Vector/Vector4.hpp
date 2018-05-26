#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector4 {
	public:


		union {
			MathType m_Data[4];
			struct { MathType X, Y, Z, W; };
		};

        template<class... EXArgs>
		FORCEINLINE TVector4(MathType X, MathType Y, MathType Z, MathType W, EXArgs&&... Ex);
		FORCEINLINE TVector4(MathType X, MathType Y, MathType Z, MathType W);
		FORCEINLINE TVector4(MathType X, MathType Y, MathType Z);
		FORCEINLINE TVector4(MathType X, MathType Y);
		FORCEINLINE TVector4(MathType Scalar);
		FORCEINLINE TVector4();
		FORCEINLINE TVector4(const TVector4<MathType>& Other);

		FORCEINLINE ~TVector4();

		FORCEINLINE TVector4<MathType>& Add(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& Subtract(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& Multiply(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& Divide(const TVector4<MathType>& Other);

		FORCEINLINE friend TVector4<MathType> operator+(TVector4<MathType> Left, const TVector4<MathType>& Right);
		FORCEINLINE friend TVector4<MathType> operator-(TVector4<MathType> Left, const TVector4<MathType>& Right);
		FORCEINLINE friend TVector4<MathType> operator*(TVector4<MathType> Left, const TVector4<MathType>& Right);
		FORCEINLINE friend TVector4<MathType> operator/(TVector4<MathType> Left, const TVector4<MathType>& Right);

		FORCEINLINE TVector4<MathType>& operator+=(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& operator-=(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& operator*=(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& operator/=(const TVector4<MathType>& Other) { return this->Divide(Other); }

		FORCEINLINE bool operator==(const TVector4<MathType>& Other);
		FORCEINLINE bool operator!=(const TVector4<MathType>& Other);

		FORCEINLINE void operator++();
		FORCEINLINE void operator--();

		FORCEINLINE TVector4<MathType>& operator++(int);
		FORCEINLINE TVector4<MathType>& operator--(int);

		FORCEINLINE MathType operator[](size_t Index);

		FORCEINLINE MathType Length();
		FORCEINLINE TVector4<MathType>& Normalize();
		FORCEINLINE MathType Dot(const TVector4<MathType>& Other);
		FORCEINLINE TVector4<MathType>& Rotate(MathType Angle);
	};

	template<class MathType>
	using TVec4 = TVector4<MathType>;

	using Vec4 = TVec4<MATH_TYPE>;
	using Vector4 = Vec4;

} }

#include "Vector4.inl"