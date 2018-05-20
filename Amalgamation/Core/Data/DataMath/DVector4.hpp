#pragma once

#include "../../Math/MathDefines.hpp"
#include "../TypeStruct.hpp"
#include "../../Platform/Typedef.hpp"

#include <cmath>

namespace Amalgamation { namespace Math {

	template<class MathType>
	union TDataVector4 {
		TypeStruct<MathType, 4> Data;
		struct { MathType X, Y, Z, W; };
	};

	using DVector4 = TDataVector4<MATH_TYPE>;
	using DVec4    = DVector4;

	//======================================================================
	// Simple Data Vector Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector4<MathType> operator + (const TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		return TDataVector4<MathType>{
			L.X + R.X, L.Y + R.Y, L.Z + R.Z, L.W + R.W
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType> operator - (const TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		return TDataVector4<MathType>{
			L.X - R.X, L.Y - R.Y, L.Z - R.Z, L.W - R.W
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType> operator * (const TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		return TDataVector4<MathType>{
			L.X * R.X, L.Y * R.Y, L.Z * R.Z, L.W * R.W
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType> operator / (const TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		return TDataVector4<MathType>{
			L.X / R.X, L.Y / R.Y, L.Z / R.Z, L.W / R.W
		};
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType> operator + (const TDataVector4<MathType>& L, T Scalar) {
		return TDataVector4<MathType>{
			L.X + Scalar, L.Y + Scalar, L.Z + Scalar, L.W + Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType> operator - (const TDataVector4<MathType>& L, T Scalar) {
		return TDataVector4<MathType>{
			L.X - Scalar, L.Y - Scalar, L.Z - Scalar, L.W - Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType> operator * (const TDataVector4<MathType>& L, T Scalar) {
		return TDataVector4<MathType>{
			L.X * Scalar, L.Y * Scalar, L.Z * Scalar, L.W * Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType> operator / (const TDataVector4<MathType>& L, T Scalar) {
		return TDataVector4<MathType>{
			L.X / Scalar, L.Y / Scalar, L.Z / Scalar, L.W / Scalar
		};
	}

	//======================================================================
	// Data Vector Data Modifying Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector4<MathType>& operator += (TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		L.X += R.X; L.Y += R.Y; L.Z += R.Z; L.W += R.W;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType>& operator -= (TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		L.X -= R.X; L.Y -= R.Y; L.Z -= R.Z; L.W -= R.W;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType>& operator *= (TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		L.X *= R.X; L.Y *= R.Y; L.Z *= R.Z; L.W *= R.W;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector4<MathType>& operator /= (TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		L.X /= R.X; L.Y /= R.Y; L.Z /= R.Z; L.W /= R.W;
		return L;
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType>& operator += (TDataVector4<MathType>& L, T Scalar) {
		L.X += Scalar; L.Y += Scalar; L.Z += Scalar; L.W += Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType>& operator -= (TDataVector4<MathType>& L, T Scalar) {
		L.X -= Scalar; L.Y -= Scalar; L.Z -= Scalar; L.W -= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType>& operator *= (TDataVector4<MathType>& L, T Scalar) {
		L.X *= Scalar; L.Y *= Scalar; L.Z *= Scalar; L.W *= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector4<MathType>& operator /= (TDataVector4<MathType>& L, T Scalar) {
		L.X /= Scalar; L.Y /= Scalar; L.Z /= Scalar; L.W /= Scalar;
		return L;
	}

	//======================================================================
	// Simple Data Vector Math Functions
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector4<MathType> Dot(const TDataVector4<MathType>& L, const TDataVector4<MathType>& R) {
		return { L.X * R.X + L.Y * R.Y + L.Z * R.Z + L.W * R.W };
	}

	template<class MathType>
	FORCEINLINE MATH_TYPE Length(const TDataVector4<MathType>& Vec) {
		return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z + Vec.W * Vec.W);
	}

	template<class MathType>
	FORCEINLINE TDataVector4<MathType> Normalize(const TDataVector4<MathType>& Vec) {
		return { const_cast<TDataVector4<MathType>&>(Vec) /= Length(Vec) };
	}

} }
