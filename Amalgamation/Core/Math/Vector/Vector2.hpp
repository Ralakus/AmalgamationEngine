#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector2 {

		using TVec2 = TVector2<MathType>;

	public:

		union {
			MathType m_Data[2];
			struct { MathType X, Y; };
		};

		FORCEINLINE TVector2(MathType X, MathType Y) : m_Data{ X, Y}
		{}

		FORCEINLINE TVector2(MathType Scalar) : m_Data{ Scalar, Scalar }
		{}

		FORCEINLINE TVector2() : m_Data{ 0, 0 }
		{}

		FORCEINLINE TVector2(const TVec2& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1]}
		{}

		/*FORCEINLINE void operator = (const TVec2& Other) {
		    memcpy(&m_data, &Other.m_Data, sizeof(MathType) * 2);
		}*/

		FORCEINLINE ~TVector2() {}

		FORCEINLINE TVec2& Add(const TVec2& Other) {
			this->X += Other.X;
			this->Y += Other.Y;
			return *this;
		}

		FORCEINLINE TVec2& Subtract(const TVec2& Other) {
			this->X -= Other.X;
			this->Y -= Other.Y;
			return *this;
		}

		FORCEINLINE TVec2& Multiply(const TVec2& Other) {
			this->X *= Other.X;
			this->Y *= Other.Y;
			return *this;
		}

		FORCEINLINE TVec2& Divide(const TVec2& Other) {
			this->X /= Other.X;
			this->Y /= Other.Y;
			return *this;
		}

		FORCEINLINE friend TVec2 operator+(TVec2 Left, const TVec2& Right) { return Left.Add(Right); }
		FORCEINLINE friend TVec2 operator-(TVec2 Left, const TVec2& Right) { return Left.Subtract(Right); }
		FORCEINLINE friend TVec2 operator*(TVec2 Left, const TVec2& Right) { return Left.Multiply(Right); }
		FORCEINLINE friend TVec2 operator/(TVec2 Left, const TVec2& Right) { return Left.Divide(Right); }

		FORCEINLINE TVec2& operator+=(const TVec2& Other) { return this->Add(Other); }
		FORCEINLINE TVec2& operator-=(const TVec2& Other) { return this->Subtract(Other); }
		FORCEINLINE TVec2& operator*=(const TVec2& Other) { return this->Multiply(Other); }
		FORCEINLINE TVec2& operator/=(const TVec2& Other) { return this->Divide(Other); }

		FORCEINLINE bool operator==(const TVec2& Other) { return (this->X == Other.X && this->Y == Other.Y); }
		FORCEINLINE bool operator!=(const TVec2& Other) { return !(*this == Other); }

		FORCEINLINE void operator++() { X++; Y++; }
		FORCEINLINE void operator--() { X--; Y--; }

        FORCEINLINE TVec2& operator++(int) { TVec2 T = *this; ++*this; return T; }
		FORCEINLINE TVec2& operator--(int) { TVec2 T = *this; --*this; return T; }

		FORCEINLINE MathType operator[](size_t Index) { return m_Data[Index]; }

		FORCEINLINE MathType Length() {
		    return sqrt(X * X + Y * Y);
		}

        FORCEINLINE TVec2& Normalize(){
            return ((*this) /= this->Length());
        }

        FORCEINLINE MathType Dot(const TVec2& Other){
            return (X * Other.X + Y * Other. Y);
        }

        FORCEINLINE TVec2& Rotate(MathType Angle){
            return *this;
        }

	};

	template<class MathType>
	using TVec2 = TVector2<MathType>;

	using Vec2 = TVec2<MATH_TYPE>;
	using Vector2 = Vec2;

} }
