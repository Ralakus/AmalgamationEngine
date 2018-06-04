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

		FORCEINLINE TVector3<MathType>& Add     (MathType Scalar);
		FORCEINLINE TVector3<MathType>& Subtract(MathType Scalar);
		FORCEINLINE TVector3<MathType>& Multiply(MathType Scalar);
		FORCEINLINE TVector3<MathType>& Divide  (MathType Scalar);

		FORCEINLINE friend TVector3<MathType> operator+(TVector3<MathType> Left, const TVector3<MathType>& Right){ return Left.Add(Right); }
		FORCEINLINE friend TVector3<MathType> operator-(TVector3<MathType> Left, const TVector3<MathType>& Right){ return Left.Subtract(Right); }
		FORCEINLINE friend TVector3<MathType> operator*(TVector3<MathType> Left, const TVector3<MathType>& Right){ return Left.Multiply(Right); }
		FORCEINLINE friend TVector3<MathType> operator/(TVector3<MathType> Left, const TVector3<MathType>& Right){ return Left.Divide(Right); }

		FORCEINLINE friend TVector3<MathType> operator+(TVector3<MathType> Left, MathType Scalar) { return Left.Add(Scalar); }
		FORCEINLINE friend TVector3<MathType> operator-(TVector3<MathType> Left, MathType Scalar) { return Left.Subtract(Scalar); }
		FORCEINLINE friend TVector3<MathType> operator*(TVector3<MathType> Left, MathType Scalar) { return Left.Multiply(Scalar); }
		FORCEINLINE friend TVector3<MathType> operator/(TVector3<MathType> Left, MathType Scalar) { return Left.Divide(Scalar); }

		FORCEINLINE TVector3<MathType>& operator+=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator-=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator*=(const TVector3<MathType>& Other);
		FORCEINLINE TVector3<MathType>& operator/=(const TVector3<MathType>& Other);

		FORCEINLINE TVector3<MathType>& operator-=(MathType Scalar) { return this->Subtract(Scalar); }
		FORCEINLINE TVector3<MathType>& operator*=(MathType Scalar) { return this->Multiply(Scalar); }
		FORCEINLINE TVector3<MathType>& operator/=(MathType Scalar) { return this->Divide(Scalar); }
		FORCEINLINE TVector3<MathType>& operator+=(MathType Scalar) { return this->Add(Scalar); } 

		FORCEINLINE bool operator==(const TVector3<MathType>& Other);
		FORCEINLINE bool operator!=(const TVector3<MathType>& Other);

		FORCEINLINE TVector3<MathType> operator++();
		FORCEINLINE TVector3<MathType> operator--();

		FORCEINLINE TVector3<MathType>& operator++(int);
		FORCEINLINE TVector3<MathType>& operator--(int);

		FORCEINLINE MathType operator[](size_t Index);

	};

	template<class MathType>
	FORCEINLINE MathType Length(const TVector3<MathType>& Vec);

	template<class MathType>
	FORCEINLINE TVector3<MathType> Normalize(const TVector3<MathType>& Vec);

	template<class MathType>
	FORCEINLINE MathType Dot(const TVector3<MathType>& Vec1, const TVector3<MathType>& Vec2);

	template<class MathType>
	FORCEINLINE TVector3<MathType> Rotate(const TVector3<MathType>& Vec, MathType Angle);

	template<class MathType>
	FORCEINLINE TVector3<MathType> Cross(const TVector3<MathType>& Vec1, const TVector3<MathType>& Vec2);


	template<class MathType>
	using TVec3 = TVector3<MathType>;

	using Vec3 = TVec3<MATH_TYPE>;
	using Vector3 = Vec3;

} }

#include "Vector3.inl"