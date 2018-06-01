#pragma once

#include "../../Platform/Platform.hpp"
#include "../Vector/Vector3.hpp"
#include "../Vector/Vector4.hpp"
#include "../Quaternion/Quaternion.hpp"
#include "../MathFunctions.hpp"
#include <cmath>
#include <cstring>

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TMatrix4x4 {

	public:

        union{
            TVector4<MathType> m_Data[4];
            MathType Elements [4][4];
			MathType Arr[16];
        };

		FORCEINLINE TMatrix4x4(MathType Diagonal);
		FORCEINLINE TMatrix4x4();
		FORCEINLINE TMatrix4x4(const TMatrix4x4& Other);
		FORCEINLINE ~TMatrix4x4();

		FORCEINLINE TMatrix4x4<MathType>& Multiply(const TMatrix4x4<MathType>& Other);
		FORCEINLINE TMatrix4x4<MathType>& Multiply(const TQuaternion<MathType>& Other);

		FORCEINLINE TVector4<MathType> Multiply(const TVector4<MathType>& Other) const;
		FORCEINLINE TVector3<MathType> Multiply(const TVector3<MathType>& Other) const;

		FORCEINLINE static TMatrix4x4<MathType> Translate(const TVector3<MathType>& Translation);
		FORCEINLINE static TMatrix4x4<MathType> Scale(const TVector3<MathType>& Scale);
		FORCEINLINE static TMatrix4x4<MathType> Identity();

		FORCEINLINE static TMatrix4x4<MathType> Orthographic(MathType Left, MathType Right, MathType Bottom, MathType Top, MathType Near, MathType Far);
		FORCEINLINE static TMatrix4x4<MathType> Perspective(float FOV, float AspectRatio, float Near, float Far);

		FORCEINLINE static TMatrix4x4<MathType> Rotate(float Angle, const TVector3<MathType>& Axis);

		FORCEINLINE friend TMatrix4x4<MathType> operator*(TMatrix4x4<MathType> Left, const TMatrix4x4<MathType>& Right)  { return Left.Multiply(Right); }
		FORCEINLINE friend TVector3<MathType> operator*(TMatrix4x4<MathType> Left, const TVector3<MathType>& Right)      { return Left.Multiply(Right); }
		FORCEINLINE friend TVector3<MathType> operator*(const TVector3<MathType>& Left, TMatrix4x4<MathType> Right)      { return Right.Multiply(Left); }
		FORCEINLINE friend TVector4<MathType> operator*(TMatrix4x4<MathType> Left, const TVector4<MathType>& Right)      { return Left.Multiply(Right); }
		FORCEINLINE friend TVector4<MathType> operator*(const TVector4<MathType>& Left, TMatrix4x4<MathType> Right)      { return Right.Multiply(Left); }
		FORCEINLINE friend TMatrix4x4<MathType> operator*(TMatrix4x4<MathType> Left, const TQuaternion<MathType>& Right) { return Left.Multiply(Right); }

		FORCEINLINE TMatrix4x4<MathType>& operator*=(const TMatrix4x4<MathType>& Other);
		FORCEINLINE TMatrix4x4<MathType>& operator*=(const TQuaternion<MathType>& Other);

		FORCEINLINE TVector4<MathType>& operator[](size_t Index) { return m_Data[Index]; }
		FORCEINLINE const TVector4<MathType>& operator[](size_t Index) const { return m_Data[Index]; }
	};

    template<class MathType>
	using TMat4x4 = TMatrix4x4<MathType>;

	using Mat4x4    = TMat4x4<MATH_TYPE>;
	using Matrix4x4 =  Mat4x4;

    using Mat4    = Mat4x4;
	using Matrix4 = Matrix4x4;

} }

#include "Matrix4x4.inl"