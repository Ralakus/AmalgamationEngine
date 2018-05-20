#pragma once

#include "../../Platform/Typedef.hpp"
#include "../Vector/Vector3.hpp"

namespace Amalgamation { namespace Math {

    template<class MathType>
    class TQuaternion {

        using TQuat = TQuaternion<MathType>;

    public:

		union {
			MathType m_Data[4];
			struct { MathType X, Y, Z, W; };
		};

        template<class... EXArgs>
        FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z, MathType W, EXArgs&&... Ex) : m_Data{ X, Y, Z, W }
		{}

		FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z, MathType W) : m_Data{ X, Y, Z, W }
		{}

        FORCEINLINE TQuaternion(MathType X, MathType Y, MathType Z) : m_Data{ X, Y, Z, 0 }
		{}

        FORCEINLINE TQuaternion(MathType X, MathType Y) : m_Data{ X, Y, 0, 0 }
		{}

		FORCEINLINE TQuaternion(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar }
		{}

		FORCEINLINE TQuaternion() : m_Data{ 0, 0, 0, 0 }
		{}

		FORCEINLINE TQuaternion(const TQuat& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] }
		{}

		FORCEINLINE void operator = (const TQuat& Other) {
		    memcpy(&m_Data, &Other.m_Data, sizeof(MathType) * 4);
		}

		FORCEINLINE ~TQuaternion() {}


		FORCEINLINE TQuat& Multiply(const TQuat& Other) {
			this->X = X * Other.W + W * Other.X + Y * Other.Z - Z * Other.Y;
			this->Y = Y * Other.W + W * Other.Y + Z * Other.X - X * Other.Z;
			this->Z = Z * Other.W + W * Other.Z + X * Other.Y - Y * Other.X;
			this->W = W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z;
			return *this;
		}

        FORCEINLINE TQuat& Multiply(const TVec3<MathType>& Other) {
			this->X =  W * Other.X + Y * Other.Z - Z * Other.Y;
			this->Y =  W * Other.Y + Z * Other.X - X * Other.Z;
			this->Z =  W * Other.Z + X * Other.Y - Y * Other.X;
			this->W = -X * Other.X - Y * Other.Y - Z * Other.Z;
			return *this;
		}


		FORCEINLINE friend TQuat operator*(TQuat Left, const TQuat& Right) { return Left.Multiply(Right); }

		FORCEINLINE friend TQuat operator*(TQuat Left, const TVec3<MathType>& Right) { return Left.Multiply(Right); }
		FORCEINLINE friend TQuat operator*(const TVec3<MathType>& Left, TQuat Right) { return Right.Multiply(Left); }

		FORCEINLINE TQuat& operator*=(const TQuat& Other) { return this->Multiply(Other); }
		FORCEINLINE TQuat& operator*=(const TVec3<MathType>& Other) { return this->Multiply(Other); }

		FORCEINLINE bool operator==(const TQuat& Other) {
			return (this->m_Data[0] == Other.m_Data[0]
				 && this->m_Data[1] == Other.m_Data[1]
				 && this->m_Data[2] == Other.m_Data[2]
				 && this->m_Data[3] == Other.m_Data[3]
			);
		}
		FORCEINLINE bool operator!=(const TQuat& Other) { return !(*this == Other); }

		FORCEINLINE MathType Length() {
		    return sqrt(X * X + Y * Y + Z * Z + W * W);
		}

        FORCEINLINE TQuat& Normalize(){
            return ((*this) /= this->Length());
        }

        FORCEINLINE TQuat Conjugate() const{
            return TQuat(-this->X, -this->Y, -this->Z, this->W);
        }

    };

    template<class MathType>
	using TQuat = TQuaternion<MathType>;

	using Quat       = TQuat<MATH_TYPE>;
	using Quaternion =  Quat;

} }
