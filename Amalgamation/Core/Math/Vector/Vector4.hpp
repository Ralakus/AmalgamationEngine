#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	class TVector4 {

	public:

		union {
			T Value[4];
			struct { T X, Y, Z, W; };
		};

        template<class... EXArgs>
		FORCEINLINE TVector4(T X, T Y, T Z, T W, EXArgs&&... Ex);
		FORCEINLINE TVector4(T X, T Y, T Z, T W);
		FORCEINLINE TVector4(T X, T Y, T Z);
		FORCEINLINE TVector4(T X, T Y);
		FORCEINLINE TVector4(T Scalar);
		FORCEINLINE TVector4();
		FORCEINLINE TVector4(const TVector4<T>& Other);

		FORCEINLINE ~TVector4();

		FORCEINLINE TVector4<T>& operator+=(const TVector4<T>& Other);
		FORCEINLINE TVector4<T>& operator-=(const TVector4<T>& Other);
		FORCEINLINE TVector4<T>& operator*=(const TVector4<T>& Other);
		FORCEINLINE TVector4<T>& operator/=(const TVector4<T>& Other);

		FORCEINLINE TVector4<T>& operator+=(T Scalar);
		FORCEINLINE TVector4<T>& operator-=(T Scalar);
		FORCEINLINE TVector4<T>& operator*=(T Scalar);
		FORCEINLINE TVector4<T>& operator/=(T Scalar);

		FORCEINLINE bool operator==(const TVector4<T>& Other);
		FORCEINLINE bool operator!=(const TVector4<T>& Other);

		FORCEINLINE void operator++();
		FORCEINLINE void operator--();

		FORCEINLINE TVector4<T>& operator++(int);
		FORCEINLINE TVector4<T>& operator--(int);

		FORCEINLINE T& operator[](size_t Index);
		FORCEINLINE const T& operator[](size_t Index) const;
	};


	template<class T>
	FORCEINLINE TVector4<T> operator+(TVector4<T> Left, const TVector4<T>& Right) { return Left += Right; }
	template<class T>																		    
	FORCEINLINE TVector4<T> operator-(TVector4<T> Left, const TVector4<T>& Right) { return Left -= Right; }
	template<class T>																		     
	FORCEINLINE TVector4<T> operator*(TVector4<T> Left, const TVector4<T>& Right) { return Left *= Right; }
	template<class T>																		    
	FORCEINLINE TVector4<T> operator/(TVector4<T> Left, const TVector4<T>& Right) { return Left /= Right; }

	template<class T>
	FORCEINLINE TVector4<T> operator+(TVector4<T> Left, T Right) { return Left += Right; }
	template<class T>
	FORCEINLINE TVector4<T> operator-(TVector4<T> Left, T Right) { return Left -= Right; }
	template<class T>
	FORCEINLINE TVector4<T> operator*(TVector4<T> Left, T Right) { return Left *= Right; }
	template<class T>
	FORCEINLINE TVector4<T> operator/(TVector4<T> Left, T Right) { return Left /= Right; }

	template<class T>
	FORCEINLINE TVector4<T> operator+(T Left, TVector4<T> Right) { return Right += Left; }
	template<class T>						 
	FORCEINLINE TVector4<T> operator-(T Left, TVector4<T> Right) { return Right -= Left; }
	template<class T>						 
	FORCEINLINE TVector4<T> operator*(T Left, TVector4<T> Right) { return Right *= Left; }
	template<class T>						 
	FORCEINLINE TVector4<T> operator/(T Left, TVector4<T> Right) { return Right /= Left; }


	template<class T>
	FORCEINLINE T Length(const TVector4<T>& Vec);

	template<class T>
	FORCEINLINE TVector4<T> Normalize(const TVector4<T>& Vec);

	template<class T>
	FORCEINLINE T Dot(const TVector4<T>& Vec1, const TVector4<T>& Vec2);

	template<class T>
	FORCEINLINE TVector4<T> Rotate(const TVector4<T>& Vec, T Angle);

	template<class T>
	using TVec4 = TVector4<T>;

	using Vec4 = TVec4<MATH_TYPE>;
	using Vector4 = Vec4;

} }

#include "Vector4.inl"