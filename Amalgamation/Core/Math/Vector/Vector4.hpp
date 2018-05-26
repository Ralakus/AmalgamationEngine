#pragma once

#include "../../Platform/Platform.hpp"
#include <cmath>
#include "../MathDefines.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector4 {

		using TVec4 = TVector4<MathType>;

	public:

		union {
			MathType m_Data[4];
			struct { MathType X, Y, Z, W; };
		};

        template<class... EXArgs>
        FORCEINLINE TVector4(MathType X, MathType Y, MathType Z, MathType W, EXArgs&&... Ex) : m_Data{ X, Y, Z, W }
		{}

		FORCEINLINE TVector4(MathType X, MathType Y, MathType Z, MathType W) : m_Data{ X, Y, Z, W }
		{}

        FORCEINLINE TVector4(MathType X, MathType Y, MathType Z) : m_Data{ X, Y, Z, 0 }
		{}

        FORCEINLINE TVector4(MathType X, MathType Y) : m_Data{ X, Y, 0, 0 }
		{}

		FORCEINLINE TVector4(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar }
		{}

		FORCEINLINE TVector4() : m_Data{ 0, 0, 0, 0 }
		{}

		FORCEINLINE TVector4(const TVec4& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] }
		{}

		FORCEINLINE void operator = (const TVec4& Other) {
		    memcpy(&m_Data, &Other.m_Data, sizeof(MathType) * 4);
		}

		FORCEINLINE ~TVector4() {}

		FORCEINLINE TVec4& Add(const TVec4& Other) {
			this->m_Data[0] += Other.m_Data[0];
			this->m_Data[1] += Other.m_Data[1];
			this->m_Data[2] += Other.m_Data[2];
			this->m_Data[3] += Other.m_Data[3];
			return *this;
		}

		FORCEINLINE TVec4& Subtract(const TVec4& Other) {
			this->m_Data[0] -= Other.m_Data[0];
			this->m_Data[1] -= Other.m_Data[1];
			this->m_Data[2] -= Other.m_Data[2];
			this->m_Data[3] -= Other.m_Data[3];
			return *this;
		}

		FORCEINLINE TVec4& Multiply(const TVec4& Other) {
			this->m_Data[0] *= Other.m_Data[0];
			this->m_Data[1] *= Other.m_Data[1];
			this->m_Data[2] *= Other.m_Data[2];
			this->m_Data[3] *= Other.m_Data[3];
			return *this;
		}

		FORCEINLINE TVec4& Divide(const TVec4& Other) {
			this->m_Data[0] /= Other.m_Data[0];
			this->m_Data[1] /= Other.m_Data[1];
			this->m_Data[2] /= Other.m_Data[2];
			this->m_Data[3] /= Other.m_Data[3];
			return *this;
		}

		FORCEINLINE friend TVec4 operator+(TVec4 Left, const TVec4& Right) { return Left.Add(Right); }
		FORCEINLINE friend TVec4 operator-(TVec4 Left, const TVec4& Right) { return Left.Subtract(Right); }
		FORCEINLINE friend TVec4 operator*(TVec4 Left, const TVec4& Right) { return Left.Multiply(Right); }
		FORCEINLINE friend TVec4 operator/(TVec4 Left, const TVec4& Right) { return Left.Divide(Right); }

		FORCEINLINE TVec4& operator+=(const TVec4& Other) { return this->Add(Other); }
		FORCEINLINE TVec4& operator-=(const TVec4& Other) { return this->Subtract(Other); }
        FORCEINLINE TVec4& operator*=(const TVec4& Other) { return this->Multiply(Other); }
		FORCEINLINE TVec4& operator/=(const TVec4& Other) { return this->Divide(Other); }

		FORCEINLINE bool operator==(const TVec4& Other) {
			return (this->m_Data[0] == Other.m_Data[0]
				 && this->m_Data[1] == Other.m_Data[1]
				 && this->m_Data[2] == Other.m_Data[2]
				 && this->m_Data[3] == Other.m_Data[3]
			);
		}
		FORCEINLINE bool operator!=(const TVec4& Other) { return !(*this == Other); }

		FORCEINLINE void operator++() { X++; Y++; Z++; W++; }
		FORCEINLINE void operator--() { X--; Y--; Z--; W--; }

		FORCEINLINE TVec4& operator++(int) { TVec4 T = *this; ++*this; return T; }
		FORCEINLINE TVec4& operator--(int) { TVec4 T = *this; --*this; return T; }

		FORCEINLINE MathType operator[](size_t Index) { return m_Data[Index]; }

		FORCEINLINE MathType Length() {
		    return sqrt(X * X + Y * Y + Z * Z + W * W);
		}

        FORCEINLINE TVec4& Normalize(){
            return ((*this) /= this->Length());
        }

        FORCEINLINE MathType Dot(const TVec4& Other){
            return (X * Other.X + Y * Other. Y + Z * Other.Z + W * Other.W);
        }

        FORCEINLINE TVec4& Rotate(MathType Angle){
            return *this;
        }
	};

	template<class MathType>
	using TVec4 = TVector4<MathType>;

	using Vec4 = TVec4<MATH_TYPE>;
	using Vector4 = Vec4;

} }
