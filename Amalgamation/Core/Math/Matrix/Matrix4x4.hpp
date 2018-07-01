#pragma once

#include "../../Platform/Platform.hpp"
#include "../Vector/Vector3.hpp"
#include "../Vector/Vector4.hpp"
#include "../Quaternion/Quaternion.hpp"
#include "../MathFunctions.hpp"
#include <cmath>
#include <cstring>

namespace Amalgamation { namespace Math {

	template<class T>
	class TMatrix4x4 {

	public:

        union{
            TVector4<T> m_Data[4];
            T Elements [4][4];
			T Arr[16];
        };

		FORCEINLINE TMatrix4x4(T Diagonal);
		FORCEINLINE TMatrix4x4(T* Arr);
		FORCEINLINE TMatrix4x4(const TQuaternion<T> Quat);
		FORCEINLINE TMatrix4x4();
		FORCEINLINE TMatrix4x4(const TMatrix4x4& Other);
		FORCEINLINE ~TMatrix4x4();

		FORCEINLINE TMatrix4x4<T>& Multiply(const TMatrix4x4<T>& Other);
		FORCEINLINE TMatrix4x4<T>& Multiply(const TQuaternion<T>& Other);

		FORCEINLINE TVector4<T> Multiply(const TVector4<T>& Other) const;
		FORCEINLINE TVector3<T> Multiply(const TVector3<T>& Other) const;

		FORCEINLINE static TMatrix4x4<T> Translate(const TVector3<T>& Translation);
		FORCEINLINE static TMatrix4x4<T> Scale(const TVector3<T>& Scale);

		FORCEINLINE static TMatrix4x4<T> Translate(const TMatrix4x4& Matrix, const TVector3<T>& Translation);
		FORCEINLINE static TMatrix4x4<T> Scale(const TMatrix4x4& Matrix, const TVector3<T>& Scale);

		FORCEINLINE static TMatrix4x4<T> Identity();

		FORCEINLINE static TMatrix4x4<T> Orthographic(T Left, T Right, T Bottom, T Top, T Near, T Far);
		FORCEINLINE static TMatrix4x4<T> Perspective(float FOV, float AspectRatio, float Near, float Far);

		FORCEINLINE static TMatrix4x4<T> Rotate(float Angle, const TVector3<T>& Axis);

		FORCEINLINE friend TMatrix4x4<T> operator*(TMatrix4x4<T> Left, const TMatrix4x4<T>& Right)  { return Left.Multiply(Right); }
		FORCEINLINE friend TVector3<T>   operator*(TMatrix4x4<T> Left, const TVector3<T>& Right)    { return Left.Multiply(Right); }
		FORCEINLINE friend TVector3<T>   operator*(const TVector3<T>& Left, TMatrix4x4<T> Right)    { return Right.Multiply(Left); }
		FORCEINLINE friend TVector4<T>   operator*(TMatrix4x4<T> Left, const TVector4<T>& Right)    { return Left.Multiply(Right); }
		FORCEINLINE friend TVector4<T>   operator*(const TVector4<T>& Left, TMatrix4x4<T> Right)    { return Right.Multiply(Left); }
		FORCEINLINE friend TMatrix4x4<T> operator*(TMatrix4x4<T> Left, const TQuaternion<T>& Right) { return Left.Multiply(Right); }

		FORCEINLINE TMatrix4x4<T>& operator*=(const TMatrix4x4<T>& Other);
		FORCEINLINE TMatrix4x4<T>& operator*=(const TQuaternion<T>& Other);

		FORCEINLINE       TVector4<T>& operator[](size_t Index)       { return m_Data[Index]; }
		FORCEINLINE const TVector4<T>& operator[](size_t Index) const { return m_Data[Index]; }
	};

    template<class T>
	using TMat4x4 = TMatrix4x4<T>;

	using Mat4x4    = TMat4x4<AE_MATH_TYPE>;
	using Matrix4x4 =  Mat4x4;

    using Mat4    = Mat4x4;
	using Matrix4 = Matrix4x4;

} }

#include "Matrix4x4.inl"