#pragma once

#include "../../Platform/Platform.hpp"
#include "../MathFunctions.hpp"
#include "../Vector/Vector3.hpp"

namespace Amalgamation { namespace Math {

    template<class T>
    class TQuaternion {

    public:

		union {
			T m_Data[4];
			struct { T X, Y, Z, W; };
		};

        template<class... EXArgs>
        FORCEINLINE TQuaternion(T X, T Y, T Z, T W, EXArgs&&... Ex);
		FORCEINLINE TQuaternion(T X, T Y, T Z, T W);
		FORCEINLINE TQuaternion(T X, T Y, T Z);
		FORCEINLINE TQuaternion(T X, T Y);
		FORCEINLINE TQuaternion(T Scalar);
		FORCEINLINE TQuaternion();
		FORCEINLINE TQuaternion(const TQuaternion<T>& Other);
		FORCEINLINE TQuaternion(const TVector3<T>& Euler);
		FORCEINLINE ~TQuaternion();


		FORCEINLINE TQuaternion<T>& Multiply(const TQuaternion<T>& Other);
		FORCEINLINE TQuaternion<T>& Multiply(const TVec3<T>& Other);
		FORCEINLINE TVector3<T> RotateVec(const TVector3<T>& Other) const;

		FORCEINLINE friend TQuaternion<T> operator*(TQuaternion<T> Left, const TQuaternion<T>& Right);

		FORCEINLINE friend TQuaternion<T> operator*(TQuaternion<T> Left, const TVec3<T>& Right);
		FORCEINLINE friend TQuaternion<T> operator*(const TVec3<T>& Left, TQuaternion<T> Right);

		//FORCEINLINE friend TVector3<T> operator*(const TQuaternion<T>& Left, const TVec3<T>& Right);

		FORCEINLINE TQuaternion<T>& operator*=(const TQuaternion<T>& Other);
		FORCEINLINE TQuaternion<T>& operator*=(const TVec3<T>& Other);

		FORCEINLINE bool operator==(const TQuaternion<T>& Other);
		FORCEINLINE bool operator!=(const TQuaternion<T>& Other);

    };

	template<class T>
	FORCEINLINE T Length(const TQuaternion<T>& Quat);

	template<class T>
	FORCEINLINE TQuaternion<T>& Normalize(const TQuaternion<T>& Quat);

	template<class T>
	FORCEINLINE TQuaternion<T> Conjugate(const TQuaternion<T>& Quat);

	template<class T>
	FORCEINLINE TVector3<T> Euler(const TQuaternion<T>& Quat);

	template<class T>
	FORCEINLINE TQuaternion<T> AngleAxis(T Angle, const TVector3<T>& Vec);

	template<class T>
	using TQuat = TQuaternion<T>;

	using Quat = TQuat<MATH_TYPE>;
	using Quaternion = Quat;

} }

#include "Quaternion.inl"