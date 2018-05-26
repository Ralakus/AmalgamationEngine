#pragma once

#include "../../Platform/Platform.hpp"
#include "../MathFunctions.hpp"
#include "../Vector/Vector3.hpp"

namespace Amalgamation { namespace Math {

    template<class MathType>
    class TQuaternion {

    public:

		union {
			MathType m_Data[4];
			struct { MathType X, Y, Z, W; };
		};

        template<class... EXArgs>
        FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z, MathType W, EXArgs&&... Ex);
		FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z, MathType W);
		FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z);
		FORCEINLINE TQuaternion(MathType X, MathType Y);
		FORCEINLINE TQuaternion(MathType Scalar);
		FORCEINLINE TQuaternion();
		FORCEINLINE TQuaternion(const TQuaternion<MathType>& Other);
		FORCEINLINE TQuaternion(const TVector3<MathType>& Euler);
		FORCEINLINE ~TQuaternion();


		FORCEINLINE TQuaternion<MathType>& Multiply(const TQuaternion<MathType>& Other);
		FORCEINLINE TQuaternion<MathType>& Multiply(const TVec3<MathType>& Other);

		FORCEINLINE friend TQuaternion<MathType> operator*(TQuaternion<MathType> Left, const TQuaternion<MathType>& Right);

		FORCEINLINE friend TQuaternion<MathType> operator*(TQuaternion<MathType> Left, const TVec3<MathType>& Right);
		FORCEINLINE friend TQuaternion<MathType> operator*(const TVec3<MathType>& Left, TQuaternion<MathType> Right);

		FORCEINLINE TQuaternion<MathType>& operator*=(const TQuaternion<MathType>& Other);
		FORCEINLINE TQuaternion<MathType>& operator*=(const TVec3<MathType>& Other);

		FORCEINLINE bool operator==(const TQuaternion<MathType>& Other);
		FORCEINLINE bool operator!=(const TQuaternion<MathType>& Other);

		FORCEINLINE MathType Length();
		FORCEINLINE TQuaternion<MathType>& Normalize();
		FORCEINLINE TQuaternion<MathType> Conjugate() const;
		FORCEINLINE TVector3<MathType> Euler() const;

    };

	template<class MathType>
	using TQuat = TQuaternion<MathType>;

	using Quat = TQuat<MATH_TYPE>;
	using Quaternion = Quat;

} }

#include "Quaternion.inl"