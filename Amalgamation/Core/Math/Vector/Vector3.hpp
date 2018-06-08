#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	class TQuaternion;

	template<class T>
	class TVector3 {

	public:

		union {
			T Value[3];
			struct { T X, Y, Z; };
			struct { T Yaw, Pitch, Roll; };
		};

        template<class... EXArgs>
		FORCEINLINE TVector3(T X, T Y, T Z, EXArgs&&... Ex);
		FORCEINLINE TVector3(T X, T Y, T Z);
		FORCEINLINE TVector3(T X, T Y);
		FORCEINLINE TVector3(T Scalar);
		FORCEINLINE TVector3();
		FORCEINLINE TVector3(const TVector3<T>& Other);

		FORCEINLINE ~TVector3();

		FORCEINLINE TVector3<T>& operator+=(const TVector3<T>& Other);
		FORCEINLINE TVector3<T>& operator-=(const TVector3<T>& Other);
		FORCEINLINE TVector3<T>& operator*=(const TVector3<T>& Other);
		FORCEINLINE TVector3<T>& operator/=(const TVector3<T>& Other);

		FORCEINLINE TVector3<T>& operator-=(T Scalar);
		FORCEINLINE TVector3<T>& operator*=(T Scalar);
		FORCEINLINE TVector3<T>& operator/=(T Scalar);
		FORCEINLINE TVector3<T>& operator+=(T Scalar);

		FORCEINLINE TVector3<T>& operator*=(const TQuaternion<T>& Other);

		FORCEINLINE bool operator==(const TVector3<T>& Other);
		FORCEINLINE bool operator!=(const TVector3<T>& Other);

		FORCEINLINE TVector3<T> operator++();
		FORCEINLINE TVector3<T> operator--();

		FORCEINLINE TVector3<T>& operator++(int);
		FORCEINLINE TVector3<T>& operator--(int);

		FORCEINLINE T& operator[](size_t Index);
		FORCEINLINE const T& operator[](size_t Index) const;

	};




	template<class T>
	FORCEINLINE TVector3<T> operator+(TVector3<T> Left, const TVector3<T>& Right) { return Left += Right; }
	template<class T>
	FORCEINLINE TVector3<T> operator-(TVector3<T> Left, const TVector3<T>& Right) { return Left -= Right; }
	template<class T>
	FORCEINLINE TVector3<T> operator*(TVector3<T> Left, const TVector3<T>& Right) { return Left *= Right; }
	template<class T>
	FORCEINLINE TVector3<T> operator/(TVector3<T> Left, const TVector3<T>& Right) { return Left /= Right; }

	template<class T>
	FORCEINLINE TVector3<T> operator*(TVector3<T> Left, const TQuaternion<T>& Right) { return Left *= Right; }

	template<class T>
	FORCEINLINE TVector3<T> operator*(const TQuaternion<T>& Left, TVector3<T> Right) { return Right *= Left; }

	template<class T>
	FORCEINLINE TVector3<T> operator+(TVector3<T> Left, T Scalar) { return Left += Scalar; }
	template<class T>
	FORCEINLINE TVector3<T> operator-(TVector3<T> Left, T Scalar) { return Left -= Scalar; }
	template<class T>
	FORCEINLINE TVector3<T> operator*(TVector3<T> Left, T Scalar) { return Left *= Scalar; }
	template<class T>
	FORCEINLINE TVector3<T> operator/(TVector3<T> Left, T Scalar) { return Left /= Scalar; }

	template<class T>
	FORCEINLINE TVector3<T> operator+(T Scalar, TVector3<T> Right) { return Right += Scalar; }
	template<class T>						  				
	FORCEINLINE TVector3<T> operator-(T Scalar, TVector3<T> Right) { return Right -= Scalar; }
	template<class T>						 				
	FORCEINLINE TVector3<T> operator*(T Scalar, TVector3<T> Right) { return Right *= Scalar; }
	template<class T>						  				
	FORCEINLINE TVector3<T> operator/(T Scalar, TVector3<T> Right) { return Right /= Scalar; }


	template<class T>
	FORCEINLINE T Length(const TVector3<T>& Vec);

	template<class T>
	FORCEINLINE TVector3<T> Normalize(const TVector3<T>& Vec);

	template<class T>
	FORCEINLINE T Dot(const TVector3<T>& Vec1, const TVector3<T>& Vec2);

	template<class T>
	FORCEINLINE TVector3<T> Rotate(const TVector3<T>& Vec, T Angle);

	template<class T>
	FORCEINLINE TVector3<T> Cross(const TVector3<T>& Vec1, const TVector3<T>& Vec2);


	template<class T>
	using TVec3 = TVector3<T>;

	using Vec3 = TVec3<MATH_TYPE>;
	using Vector3 = Vec3;

} }

#include "Vector3.inl"