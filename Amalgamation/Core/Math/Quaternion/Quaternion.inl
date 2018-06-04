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

	template<class MathType>
	FORCEINLINE TVector3<MathType> TQuaternion<MathType>::RotateVec(const TVector3<MathType>& Other) const {

		/*tvec3<T, P> const QuatVector(q.x, q.y, q.z);
		tvec3<T, P> const uv(glm::cross(QuatVector, v));
		tvec3<T, P> const uuv(glm::cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<T>(2);*/

		TVector3<MathType> QuatVector(this->X, this->Y, this->Z);
		TVector3<MathType> UV(Cross(QuatVector, Other));
		TVector3<MathType> UUV(Cross(QuatVector, UV));

		return Other + ((UV * this->W) + UUV) * static_cast<MathType>(2);

	}

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
	FORCEINLINE TQuaternion<MathType>operator*(TQuaternion<MathType>Left, const TQuaternion<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>operator*(TQuaternion<MathType>Left, const TVec3<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>operator*(const TVec3<MathType>& Left, TQuaternion<MathType>Right)
	{ return Right.Multiply(Left); }


	template<class MathType>
	FORCEINLINE TVector3<MathType> operator*(const TQuaternion<MathType>& Left, const TVec3<MathType>& Right) {
		return Left.RotateVec(Right);
	}




	template<class MathType>
	FORCEINLINE MathType Length(const TQuaternion<MathType>& Quat)
	{ return sqrt(Quat.X * Quat.X + Quat.Y * Quat.Y + Quat.Z * Quat.Z + Quat.W * Quat.W); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType>& Normalize(const TQuaternion<MathType>& Quat)
	{ return ( Quat / Length(Quat) ); }

	template<class MathType>
	FORCEINLINE TQuaternion<MathType> Conjugate(const TQuaternion<MathType>& Quat)
	{ return { -Quat.X, -Quat.Y, -Quat.Z, Quat.W }; }

	template<class MathType>
	FORCEINLINE TVector3<MathType> Euler(const TQuaternion<MathType>& Quat) {
		MathType SQX = Quat.X * Quat.X;
		MathType SQY = Quat.Y * Quat.Y;
		MathType SQZ = Quat.Z * Quat.Z;
		MathType SQW = Quat.W * Quat.W;
		return {
			static_cast<MathType>(Math::Degrees(atan2(2.0  * (Quat.Y * Quat.Z + Quat.X * Quat.W), (-SQX - SQY + SQZ + SQW)))),
			static_cast<MathType>(Math::Degrees(asin(-2.0 *  (Quat.X * Quat.Z - Quat.Y * Quat.W)))),
			static_cast<MathType>(Math::Degrees(atan2(2.0  * (Quat.X * Quat.Y + Quat.Z * Quat.W), (SQX - SQY - SQZ + SQW))))
		};
	}

	template<class MathType>
	FORCEINLINE TQuaternion<MathType> AngleAxis(MathType Angle, const TVector3<MathType>& Vec) {

		return {

			Vec.X * sin(Angle * static_cast<MathType>(0.5)),
			Vec.Y * sin(Angle * static_cast<MathType>(0.5)),
			Vec.Z * sin(Angle * static_cast<MathType>(0.5)),
			        cos(Angle * static_cast<MathType>(0.5))

		};
	}


} }