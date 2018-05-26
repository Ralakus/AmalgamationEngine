#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector3 {

		using TVec3 = TVector3<MathType>;

	public:

		union {
			MathType m_Data[3];
			struct { MathType X, Y, Z; };
			struct { MathType Yaw, Pitch, Roll; };
		};

        template<class... EXArgs>
        FORCEINLINE TVector3(MathType X, MathType Y, MathType Z, EXArgs&&... Ex) : m_Data{ X, Y, Z }
		{}
		FORCEINLINE TVector3(MathType X, MathType Y, MathType Z) : m_Data{ X, Y, Z }
		{}
        FORCEINLINE TVector3(MathType X, MathType Y) : m_Data{ X, Y, 0 }
		{}
		FORCEINLINE TVector3(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar }
		{}
		FORCEINLINE TVector3() : m_Data{ 0, 0, 0 }
		{}
		FORCEINLINE TVector3(const TVec3& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2] }
		{}

		FORCEINLINE void operator = (const TVec3& Other) {
			memcpy(&m_Data, &Other.m_Data, sizeof(MathType) * 3);
		}

		FORCEINLINE ~TVector3() {}

		FORCEINLINE TVec3& Add(const TVec3& Other) {
			this->X += Other.X;
			this->Y += Other.Y;
			this->Z += Other.Z;
			return *this;
		}

		FORCEINLINE TVec3& Subtract(const TVec3& Other) {
			this->X -= Other.X;
			this->Y -= Other.Y;
			this->Z -= Other.Z;
			return *this;
		}

		FORCEINLINE TVec3& Multiply(const TVec3& Other) {
			this->X *= Other.X;
			this->Y *= Other.Y;
			this->Z *= Other.Z;
			return *this;
		}

		FORCEINLINE TVec3& Divide(const TVec3& Other) {
			this->X /= Other.X;
			this->Y /= Other.Y;
			this->Z /= Other.Z;
			return *this;
		}

		FORCEINLINE friend TVec3 operator+(TVec3 Left, const TVec3& Right) { return Left.Add(Right); }
		FORCEINLINE friend TVec3 operator-(TVec3 Left, const TVec3& Right) { return Left.Subtract(Right); }
		FORCEINLINE friend TVec3 operator*(TVec3 Left, const TVec3& Right) { return Left.Multiply(Right); }
		FORCEINLINE friend TVec3 operator/(TVec3 Left, const TVec3& Right) { return Left.Divide(Right); }

		FORCEINLINE TVec3& operator+=(const TVec3& Other) { return this->Add(Other); }
		FORCEINLINE TVec3& operator-=(const TVec3& Other) { return this->Subtract(Other); }
		FORCEINLINE TVec3& operator*=(const TVec3& Other) { return this->Multiply(Other); }
		FORCEINLINE TVec3& operator/=(const TVec3& Other) { return this->Divide(Other); }

		FORCEINLINE bool operator==(const TVec3& Other) { return (this->X == Other.X && this->Y == Other.Y && this->Z == Other.Z); }
		FORCEINLINE bool operator!=(const TVec3& Other) { return !(*this == Other); }

		FORCEINLINE TVec3 operator++() { X++; Y++; Z++; return *this; }
		FORCEINLINE TVec3 operator--() { X--; Y--; Z--; return *this; }

		FORCEINLINE TVec3& operator++(int) { TVec3 T = *this; ++*this; return T; }
		FORCEINLINE TVec3& operator--(int) { TVec3 T = *this; --*this; return T; }

		FORCEINLINE MathType operator[](size_t Index) { return m_Data[Index]; }

        FORCEINLINE MathType Length() {
		    return sqrt(X * X + Y * Y + Z * Z);
		}

        FORCEINLINE TVec3& Normalize(){
            return ((*this) /= this->Length());
        }

        FORCEINLINE MathType Dot(const TVec3& Other){
            return (X * Other.X + Y * Other. Y + Z * Other.Z);
        }

        FORCEINLINE TVec3& Rotate(MathType Angle){
            return *this;
        }

        FORCEINLINE TVec3& Cross(const TVec3& Other){
            this->X = Y * Other.Z - Z * Other.Y;
            this->Y = Z * Other.X - X * Other.Z;
            this->Z = X * Other.Y - Y * Other.X;
            return *this;
        }

	};

	template<class MathType>
	using TVec3 = TVector3<MathType>;

	using Vec3    = TVec3<MATH_TYPE>;
	using Vector3 =  Vec3;

} }
