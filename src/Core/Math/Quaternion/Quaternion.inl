#include "Quaternion.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	template<class ...EXArgs>
	FORCEINLINE TQuaternion<T>::TQuaternion(T X, T Y, T Z, T W, EXArgs && ...Ex)
		: m_Data{ X, Y, Z, W } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(T X, T Y, T Z, T W)
		: m_Data{ X, Y, Z, W } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(T X, T Y, T Z)
		: m_Data{ X, Y, Z, 0 } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(T X, T Y)
		: m_Data{ X, Y, 0, 0 } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(T Scalar)
		: m_Data{ Scalar, Scalar, Scalar } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion()
		: m_Data{ 0, 0, 0, 0 } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(const TQuaternion<T>& Other)
		: m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] } {}

	template<class T>
	FORCEINLINE TQuaternion<T>::TQuaternion(const TVector3<T>& Euler) {
		TVector3<T> C = {
			cos(Euler.X * 0.5f), cos(Euler.Y * 0.5f), cos(Euler.Z * 0.5f)
		};
		TVector3<T> S = {
			sin(Euler.X * 0.5f), sin(Euler.Y * 0.5f), sin(Euler.Z * 0.5f)
		};

		this->W = C.X * C.Y * C.Z + S.X * S.Y * S.Z;
		this->X = S.X * C.Y * C.Z - C.X * S.Y * S.Z;
		this->Y = C.X * S.Y * C.Z + S.X * C.Y * S.Z;
		this->Z = C.X * C.Y * S.Z - S.X * S.Y * C.Z;
	}

	template<class T>
	FORCEINLINE TQuaternion<T>::~TQuaternion() {}

	template<class T>
	FORCEINLINE TQuaternion<T>& TQuaternion<T>::Multiply(const TQuaternion<T>& Other) {
		this->X = X * Other.W + W * Other.X + Y * Other.Z - Z * Other.Y;
		this->Y = Y * Other.W + W * Other.Y + Z * Other.X - X * Other.Z;
		this->Z = Z * Other.W + W * Other.Z + X * Other.Y - Y * Other.X;
		this->W = W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TQuaternion<T>& TQuaternion<T>::Multiply(const TVec3<T>& Other) {
		this->X = W * Other.X + Y * Other.Z - Z * Other.Y;
		this->Y = W * Other.Y + Z * Other.X - X * Other.Z;
		this->Z = W * Other.Z + X * Other.Y - Y * Other.X;
		this->W = -X * Other.X - Y * Other.Y - Z * Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T> TQuaternion<T>::RotateVec(const TVector3<T>& Other) const {

		/*tvec3<T, P> const QuatVector(q.x, q.y, q.z);
		tvec3<T, P> const uv(glm::cross(QuatVector, v));
		tvec3<T, P> const uuv(glm::cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * static_cast<T>(2);*/

		TVector3<T> QuatVector(this->X, this->Y, this->Z);
		TVector3<T> UV(Cross(QuatVector, Other));
		TVector3<T> UUV(Cross(QuatVector, UV));

		return Other + ((UV * this->W) + UUV) * static_cast<T>(2);

	}

	template<class T>
	FORCEINLINE TQuaternion<T>& TQuaternion<T>::operator*=(const TQuaternion<T>& Other)
	{ return this->Multiply(Other); }

	template<class T>
	FORCEINLINE TQuaternion<T>& TQuaternion<T>::operator*=(const TVec3<T>& Other)
	{ return this->Multiply(Other); }

	template<class T>
	FORCEINLINE bool TQuaternion<T>::operator==(const TQuaternion<T>& Other) {
		return (this->m_Data[0] == Other.m_Data[0]
			&& this->m_Data[1] == Other.m_Data[1]
			&& this->m_Data[2] == Other.m_Data[2]
			&& this->m_Data[3] == Other.m_Data[3]
			);
	}

	template<class T>
	FORCEINLINE bool TQuaternion<T>::operator!=(const TQuaternion<T>& Other)
	{ return !(*this == Other); }

	template<class T>
	FORCEINLINE TQuaternion<T>operator*(TQuaternion<T>Left, const TQuaternion<T>& Right)
	{ return Left.Multiply(Right); }

	template<class T>
	FORCEINLINE TQuaternion<T>operator*(TQuaternion<T>Left, const TVec3<T>& Right)
	{ return Left.Multiply(Right); }

	template<class T>
	FORCEINLINE TQuaternion<T>operator*(const TVec3<T>& Left, TQuaternion<T>Right)
	{ return Right.Multiply(Left); }


	/*template<class T>
	FORCEINLINE TVector3<T> operator*(const TQuaternion<T>& Left, const TVec3<T>& Right) {
		return Left.RotateVec(Right);
	}*/




	template<class T>
	FORCEINLINE T Length(const TQuaternion<T>& Quat)
	{ return sqrt(Quat.X * Quat.X + Quat.Y * Quat.Y + Quat.Z * Quat.Z + Quat.W * Quat.W); }

	template<class T>
	FORCEINLINE TQuaternion<T>& Normalize(const TQuaternion<T>& Quat)
	{ return ( Quat / Length(Quat) ); }

	template<class T>
	FORCEINLINE TQuaternion<T> Conjugate(const TQuaternion<T>& Quat)
	{ return { -Quat.X, -Quat.Y, -Quat.Z, Quat.W }; }

	template<class T>
	FORCEINLINE TVector3<T> Euler(const TQuaternion<T>& Quat) {
		T SQX = Quat.X * Quat.X;
		T SQY = Quat.Y * Quat.Y;
		T SQZ = Quat.Z * Quat.Z;
		T SQW = Quat.W * Quat.W;
		return {
			static_cast<T>(Math::Degrees(atan2(2.0  * (Quat.Y * Quat.Z + Quat.X * Quat.W), (-SQX - SQY + SQZ + SQW)))),
			static_cast<T>(Math::Degrees(asin(-2.0 *  (Quat.X * Quat.Z - Quat.Y * Quat.W)))),
			static_cast<T>(Math::Degrees(atan2(2.0  * (Quat.X * Quat.Y + Quat.Z * Quat.W), (SQX - SQY - SQZ + SQW))))
		};
	}

	template<class T>
	FORCEINLINE TQuaternion<T> AngleAxis(T Angle, const TVector3<T>& Vec) {

		return {

			Vec.X * sin(Angle * static_cast<T>(0.5)),
			Vec.Y * sin(Angle * static_cast<T>(0.5)),
			Vec.Z * sin(Angle * static_cast<T>(0.5)),
			        cos(Angle * static_cast<T>(0.5))

		};
	}


} }