#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector3 {

	public:

		union {
			MathType m_Data[3];
			struct { MathType X, Y, Z; };
			struct { MathType Yaw, Pitch, Roll; };
		};

        template<class... EXArgs>
		FORCEINLINE TVector3(MathType X, MathType Y, MathType Z, EXArgs&&... Ex);
		FORCEINLINE TVector3(MathType X, MathType Y, MathType Z);
		FORCEINLINE TVector3(MathType X, MathType Y);
		FORCEINLINE TVector3(MathType Scalar);
		FORCEINLINE TVector3();
		FORCEINLINE TVector3(const TVector3<MathType>& Other);

		FORCEINLINE ~TVector3();

		FORCEINLINE TVector3<MathType>& Add(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& Subtract(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& Multiply(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& Divide(const TVector3<MathType>& Other);

		FORCEINLINE friend TVector3<MathType> operator+(TVector3<MathType> Left, const TVector3<MathType>& Right);
		FORCEINLINE friend TVector3<MathType> operator-(TVector3<MathType> Left, const TVector3<MathType>& Right);
		FORCEINLINE friend TVector3<MathType> operator*(TVector3<MathType> Left, const TVector3<MathType>& Right);
		FORCEINLINE friend TVector3<MathType> operator/(TVector3<MathType> Left, const TVector3<MathType>& Right);

		FORCEINLINE TVector3<MathType>& operator+=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator-=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator*=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator/=(const TVector3<MathType>& Other);

		FORCEINLINE bool operator==(const TVector3<MathType>& Other);
		FORCEINLINE bool operator!=(const TVector3<MathType>& Other);

		FORCEINLINE TVector3<MathType> operator++();
		FORCEINLINE TVector3<MathType> operator--();

		FORCEINLINE TVector3<MathType>& operator++(int);
		FORCEINLINE TVector3<MathType>& operator--(int);

		FORCEINLINE MathType operator[](size_t Index);

		FORCEINLINE MathType Length();
		FORCEINLINE TVector3<MathType>& Normalize();
		FORCEINLINE MathType Dot(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& Rotate(MathType Angle);
		FORCEINLINE TVector3<MathType>& Cross(const TVector3<MathType>& Other);

	};

	template<class MathType>
	using TVec3 = TVector3<MathType>;

	using Vec3 = TVec3<MATH_TYPE>;
	using Vector3 = Vec3;

} }

#include "Vector3.inl"