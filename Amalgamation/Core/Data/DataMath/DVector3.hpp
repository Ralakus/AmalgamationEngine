#pragma once

#include "../../Math/MathDefines.hpp"
#include "../TypeStruct.hpp"
#include "../../Platform/Typedef.hpp"

#include <cmath>

namespace Amalgamation { namespace Math {

	template<class MathType>
	union TDataVector3 {
		TypeStruct<MathType, 3> Data;
		struct { MathType X, Y, Z; };
	};

	using DVector3 = TDataVector3<MATH_TYPE>;
	using DVec3    = DVector3;

	//======================================================================
	// Simple Data Vector Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector3<MathType> operator + (const TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		return TDataVector3<MathType>{
			L.X + R.X, L.Y + R.Y, L.Z + R.Z
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType> operator - (const TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		return TDataVector3<MathType>{
			L.X - R.X, L.Y - R.Y, L.Z - R.Z
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType> operator * (const TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		return TDataVector3<MathType>{
			L.X * R.X, L.Y * R.Y, L.Z * R.Z
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType> operator / (const TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		return TDataVector3<MathType>{
			L.X / R.X, L.Y / R.Y, L.Z / R.Z
		};
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType> operator + (const TDataVector3<MathType>& L, T Scalar) {
		return TDataVector3<MathType>{
			L.X + Scalar, L.Y + Scalar, L.Z + Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType> operator - (const TDataVector3<MathType>& L, T Scalar) {
		return TDataVector3<MathType>{
			L.X - Scalar, L.Y - Scalar, L.Z - Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType> operator * (const TDataVector3<MathType>& L, T Scalar) {
		return TDataVector3<MathType>{
			L.X * Scalar, L.Y * Scalar, L.Z * Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType> operator / (const TDataVector3<MathType>& L, T Scalar) {
		return TDataVector3<MathType>{
			L.X / Scalar, L.Y / Scalar, L.Z / Scalar
		};
	}

	//======================================================================
	// Data Vector Data Modifying Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector3<MathType>& operator += (TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		L.X += R.X; L.Y += R.Y; L.Z += R.Z;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType>& operator -= (TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		L.X -= R.X; L.Y -= R.Y; L.Z -= R.Z;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType>& operator *= (TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		L.X *= R.X; L.Y *= R.Y; L.Z *= R.Z;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector3<MathType>& operator /= (TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		L.X /= R.X; L.Y /= R.Y; L.Z /= R.Z;
		return L;
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType>& operator += (TDataVector3<MathType>& L, T Scalar) {
		L.X += Scalar; L.Y += Scalar; L.Z += Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType>& operator -= (TDataVector3<MathType>& L, T Scalar) {
		L.X -= Scalar; L.Y -= Scalar; L.Z -= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType>& operator *= (TDataVector3<MathType>& L, T Scalar) {
		L.X *= Scalar; L.Y *= Scalar; L.Z *= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector3<MathType>& operator /= (TDataVector3<MathType>& L, T Scalar) {
		L.X /= Scalar; L.Y /= Scalar; L.Z /= Scalar;
		return L;
	}

	//======================================================================
	// Simple Data Vector Math Functions
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector3<MathType> Dot(const TDataVector3<MathType>& L, const TDataVector3<MathType>& R) {
		return { L.X * R.X + L.Y * R.Y + L.Z * R.Z };
	}

	template<class MathType>
	FORCEINLINE MATH_TYPE Length(const TDataVector3<MathType>& Vec) {
		return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z );
	}

	template<class MathType>
	FORCEINLINE TDataVector3<MathType> Normalize(const TDataVector3<MathType>& Vec) {
		return { const_cast<TDataVector4<MathType>&>(Vec) /= Length(Vec) };
	}

	template<class MathType>
	FORCEINLINE TDataVector3<MathType>& Cross(TDataVector3<MathType>& Vec, const TDataVector3<MathType>& Other) {
		Vec.X = Vec.Y * Other.Z - Vec.Z * Other.Y;
		Vec.Y = Vec.Z * Other.X - Vec.X * Other.Z;
		Vec.Z = Vec.X * Other.Y - Vec.Y * Other.X;
		return Vec;
	}

} }
