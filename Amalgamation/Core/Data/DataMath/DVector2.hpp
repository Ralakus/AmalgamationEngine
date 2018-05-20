#pragma once

#include "../../Math/MathDefines.hpp"
#include "../TypeStruct.hpp"
#include "../../Platform/Typedef.hpp"

#include <cmath>

namespace Amalgamation { namespace Math {

	template<class MathType>
	union TDataVector2 {
		TypeStruct<MathType, 2> Data;
		struct { MathType X, Y; };
	};

	using DVector2 = TDataVector2<MATH_TYPE>;
	using DVec2    = DVector2;

	//======================================================================
	// Simple Data Vector Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector2<MathType> operator + (const TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		return TDataVector2<MathType>{
			L.X + R.X, L.Y + R.Y
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType> operator - (const TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		return TDataVector2<MathType>{
			L.X - R.X, L.Y - R.Y
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType> operator * (const TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		return TDataVector2<MathType>{
			L.X * R.X, L.Y * R.Y
		};
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType> operator / (const TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		return TDataVector2<MathType>{
			L.X / R.X, L.Y / R.Y
		};
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType> operator + (const TDataVector2<MathType>& L, T Scalar) {
		return TDataVector2<MathType>{
			L.X + Scalar, L.Y + Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType> operator - (const TDataVector2<MathType>& L, T Scalar) {
		return TDataVector2<MathType>{
			L.X - Scalar, L.Y - Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType> operator * (const TDataVector2<MathType>& L, T Scalar) {
		return TDataVector2<MathType>{
			L.X * Scalar, L.Y * Scalar
		};
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType> operator / (const TDataVector2<MathType>& L, T Scalar) {
		return TDataVector2<MathType>{
			L.X / Scalar, L.Y / Scalar
		};
	}

	//======================================================================
	// Data Vector Data Modifying Math Operations
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector2<MathType>& operator += (TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		L.X += R.X; L.Y += R.Y;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType>& operator -= (TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		L.X -= R.X; L.Y -= R.Y;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType>& operator *= (TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		L.X *= R.X; L.Y *= R.Y;
		return L;
	}
	template<class MathType>
	FORCEINLINE TDataVector2<MathType>& operator /= (TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		L.X /= R.X; L.Y /= R.Y;
		return L;
	}

	//Scalar operations

	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType>& operator += (TDataVector2<MathType>& L, T Scalar) {
		L.X += Scalar; L.Y += Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType>& operator -= (TDataVector2<MathType>& L, T Scalar) {
		L.X -= Scalar; L.Y -= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType>& operator *= (TDataVector2<MathType>& L, T Scalar) {
		L.X *= Scalar; L.Y *= Scalar;
		return L;
	}
	template<class T, class MathType>
	FORCEINLINE TDataVector2<MathType>& operator /= (TDataVector2<MathType>& L, T Scalar) {
		L.X /= Scalar; L.Y /= Scalar;
		return L;
	}

	//======================================================================
	// Simple Data Vector Math Functions
	//======================================================================
	template<class MathType>
	FORCEINLINE TDataVector2<MathType> Dot(const TDataVector2<MathType>& L, const TDataVector2<MathType>& R) {
		return { L.X * R.X + L.Y * R.Y + L.Z };
	}

	template<class MathType>
	FORCEINLINE MATH_TYPE Length(const TDataVector2<MathType>& Vec) {
		return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y );
	}

	template<class MathType>
	FORCEINLINE TDataVector2<MathType> Normalize(const TDataVector2<MathType>& Vec) {
		return { const_cast<TDataVector4<MathType>&>(Vec) /= Length(Vec) };
	}

} }
