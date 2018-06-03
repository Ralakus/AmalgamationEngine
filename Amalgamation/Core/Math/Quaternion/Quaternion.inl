#include "Quaternion.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	template<class ...EXArgs>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(MathType X, MathType Y, MathType Z, MathType W, EXArgs && ...Ex)
		: m_Data{ X, Y, Z, W } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(MathType X, MathType Y, MathType Z, MathType W)
		: m_Data{ X, Y, Z, W } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(MathType X, MathType Y, MathType Z)
		: m_Data{ X, Y, Z, 0 } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(MathType X, MathType Y)
		: m_Data{ X, Y, 0, 0 } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(MathType Scalar)
		: m_Data{ Scalar, Scalar, Scalar } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion()
		: m_Data{ 0, 0, 0, 0 } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(const TQuaternion<MathType>& Other)
		: m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] } {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::TQuaternion(const TVector3<MathType>& Euler) {
		TVector3<MathType> C = {
			cos(Euler.X * 0.5f), cos(Euler.Y * 0.5f), cos(Euler.Z * 0.5f)
		};
		TVector3<MathType> S = {
			sin(Euler.X * 0.5f), sin(Euler.Y * 0.5f), sin(Euler.Z * 0.5f)
		};

		this->W = C.X * C.Y * C.Z + S.X * S.Y * S.Z;
		this->X = S.X * C.Y * C.Z - C.X * S.Y * S.Z;
		this->Y = C.X * S.Y * C.Z + S.X * C.Y * S.Z;
		this->Z = C.X * C.Y * S.Z - S.X * S.Y * C.Z;
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>::~TQuaternion() {}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& TQuaternion<MathType>::Multiply(const TQuaternion<MathType>& Other) {
		this->X = X * Other.W + W * Other.X + Y * Other.Z - Z * Other.Y;
		this->Y = Y * Other.W + W * Other.Y + Z * Other.X - X * Other.Z;
		this->Z = Z * Other.W + W * Other.Z + X * Other.Y - Y * Other.X;
		this->W = W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& TQuaternion<MathType>::Multiply(const TVec3<MathType>& Other) {
		this->X = W * Other.X + Y * Other.Z - Z * Other.Y;
		this->Y = W * Other.Y + Z * Other.X - X * Other.Z;
		this->Z = W * Other.Z + X * Other.Y - Y * Other.X;
		this->W = -X * Other.X - Y * Other.Y - Z * Other.Z;
		return *this;
	}

	/*template<class MathType>
	FORCEINLINE TVector3<MathType> TQuaternion<MathType>::Multiply(const TVector3<MathType>& Other) {

		tvec3<T, P> const QuatVector(q.x, q.y, q.z);
		tvec3<T, P> const uv(glm::cross(QuatVector, v));
		tvec3<T, P> const uuv(glm::cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<T>(2);

		TVector3<MathType> QuatVector(this->X, this->Y, this->Z);
		TVector3<MathType> UV(TVector3<MathType>(QuatVector).Cross(Other));
		TVector3<MathType> UUV(TVector3<MathType>(QuatVector).Cross(UV));

		return Other + ((UV * this->W) + UUV) * static_cast<MathType>(2);

	}*/

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& TQuaternion<MathType>::operator*=(const TQuaternion<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& TQuaternion<MathType>::operator*=(const TVec3<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE bool TQuaternion<MathType>::operator==(const TQuaternion<MathType>& Other) {
		return (this->m_Data[0] == Other.m_Data[0]
			&& this->m_Data[1] == Other.m_Data[1]
			&& this->m_Data[2] == Other.m_Data[2]
			&& this->m_Data[3] == Other.m_Data[3]
			);
	}

	template<class MathType>
	FORCEINLINE bool TQuaternion<MathType>::operator!=(const TQuaternion<MathType>& Other)
	{ return !(*this == Other); }

	template<class MathType>
	FORCEINLINE MathType TQuaternion<MathType>::Length() {
		return sqrt(X * X + Y * Y + Z * Z + W * W);
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& TQuaternion<MathType>::Normalize() {
		return ((*this) /= this->Length());
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType> TQuaternion<MathType>::Conjugate() const {
		return TQuaternion<MathType>(-this->X, -this->Y, -this->Z, this->W);
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType> TQuaternion<MathType>::Euler() const {
		MathType SQX = this->X * this->X;
		MathType SQY = this->Y * this->Y;
		MathType SQZ = this->Z * this->Z;
		MathType SQW = this->W * this->W;
		return TVector3<MathType>(
			Math::Degrees(atan2(2.0  * (this->Y * this->Z + this->X * this->W), (-SQX - SQY + SQZ + SQW))),
			Math::Degrees(asin(-2.0 * (this->X * this->Z - this->Y * this->W))),
			Math::Degrees(atan2(2.0  * (this->X * this->Y + this->Z * this->W), (SQX - SQY - SQZ + SQW)))
		);
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>operator*(TQuaternion<MathType>Left, const TQuaternion<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>operator*(TQuaternion<MathType>Left, const TVec3<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>operator*(const TVec3<MathType>& Left, TQuaternion<MathType>Right)
	{ return Right.Multiply(Left); }

} }