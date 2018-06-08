#include "../Quaternion/Quaternion.hpp"
#include "Vector3.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	template<class ...EXArgs>
	FORCEINLINE TVector3<T>::TVector3(T X, T Y, T Z, EXArgs && ...Ex)
		: Value{ X, Y, Z } {}

	template<class T>
	FORCEINLINE Amalgamation::Math::TVector3<T>::TVector3(T X, T Y, T Z)
		: Value{ X, Y, Z } {}

	template<class T>
	FORCEINLINE TVector3<T>::TVector3(T X, T Y)
		: Value{ X, Y, 0 } {}

	template<class T>
	FORCEINLINE TVector3<T>::TVector3(T Scalar)
		: Value{ Scalar, Scalar, Scalar } {}

	template<class T>
	FORCEINLINE TVector3<T>::TVector3()
		: Value{ 0, 0, 0 } {}

	template<class T>
	FORCEINLINE TVector3<T>::TVector3(const TVector3<T> & Other)
		: Value{ Other.Value[0], Other.Value[1], Other.Value[2] } {}

	template<class T>
	FORCEINLINE TVector3<T>::~TVector3()
	{}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator+=(const TVector3<T>& Other) {
		this->X += Other.X;
		this->Y += Other.Y;
		this->Z += Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator-=(const TVector3<T>& Other) {
		this->X -= Other.X;
		this->Y -= Other.Y;
		this->Z -= Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator*=(const TVector3<T>& Other) {
		this->X *= Other.X;
		this->Y *= Other.Y;
		this->Z *= Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator/=(const TVector3<T>& Other) {
		this->X /= Other.X;
		this->Y /= Other.Y;
		this->Z /= Other.Z;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator-=(T Scalar) {
		this->X -= Scalar;
		this->Y -= Scalar;
		this->Z -= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator*=(T Scalar) {
		this->X *= Scalar;
		this->Y *= Scalar;
		this->Z *= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator/=(T Scalar) {
		this->X /= Scalar;
		this->Y /= Scalar;
		this->Z /= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator+=(T Scalar) {
		this->X += Scalar;
		this->Y += Scalar;
		this->Z += Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator*=(const TQuaternion<T>& Other) {
		TVector3<T> QuatVector(Other.X, Other.Y, Other.Z);
		TVector3<T> UV(Cross(QuatVector, *this));
		TVector3<T> UUV(Cross(QuatVector, UV));

		return *this + ((UV * this->W) + UUV) * static_cast<T>(2);
	}

	template<class T>
	FORCEINLINE bool TVector3<T>::operator==(const TVector3<T>& Other)
	{ return (this->X == Other.X && this->Y == Other.Y && this->Z == Other.Z); }

	template<class T>
	FORCEINLINE bool TVector3<T>::operator!=(const TVector3<T>& Other)
	{ return !(*this == Other); }

	template<class T>
	FORCEINLINE TVector3<T> TVector3<T>::operator++()
	{ X++; Y++; Z++; return *this; }

	template<class T>
	FORCEINLINE TVector3<T> TVector3<T>::operator--()
	{ X--; Y--; Z--; return *this; }

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator++(int)
	{ TVector3<T> Temp = *this; ++*this; return Temp; }

	template<class T>
	FORCEINLINE TVector3<T>& TVector3<T>::operator--(int)
	{ TVector3<T> Temp = *this; --*this; return Temp; }

	template<class T>
	FORCEINLINE T& TVector3<T>::operator[](size_t Index)
	{ return Value[Index]; }

	template<class T>
	FORCEINLINE const T & TVector3<T>::operator[](size_t Index) const
	{ return Value[Index]; }


	template<class T>
	FORCEINLINE T Length(const TVector3<T>& Vec)
	{ return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z); }

	template<class T>
	FORCEINLINE TVector3<T> Normalize(const TVector3<T>& Vec)
	{ return (  Vec / Length(Vec)  ); }

	template<class T>
	FORCEINLINE T Dot(const TVector3<T>& Vec1, const TVector3<T>& Vec2)
	{ return (Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z); }

	template<class T>
	FORCEINLINE TVector3<T> Rotate(const TVector3<T>& Vec, T Angle)
	{ return Vec; }

	template<class T>
	FORCEINLINE TVector3<T> Cross(const TVector3<T>& Vec1, const TVector3<T>& Vec2) {
		return {
			Vec1.Y * Vec2.Z - Vec1.Z * Vec2.Y,
			Vec1.Z * Vec2.X - Vec1.X * Vec2.Z,
			Vec1.X * Vec2.Y - Vec1.Y * Vec2.X,
		};
	}


} }