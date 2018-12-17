#include "Vector4.hpp"

namespace Amalgamation { namespace Math {

	template<class T>
	template<class ...EXArgs>
	FORCEINLINE TVector4<T>::TVector4(T X, T Y, T Z, T W, EXArgs && ...Ex)
		: Value{ X, Y, Z, W } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4(T X, T Y, T Z, T W)
		: Value{ X, Y, Z, W } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4(T X, T Y, T Z)
		: Value{ X, Y, Z, 0 } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4(T X, T Y)
		: Value{ X, Y, 0, 0 } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4(T Scalar)
		: Value{ Scalar, Scalar, Scalar } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4()
		: Value{ 0, 0, 0, 0 } {}

	template<class T>
	FORCEINLINE TVector4<T>::TVector4(const TVector4<T> & Other)
		: Value{ Other.Value[0], Other.Value[1], Other.Value[2], Other.Value[3] } {}

	template<class T>
	FORCEINLINE TVector4<T>::~TVector4()
	{}

	template<class T>
	FORCEINLINE TVector4<T> & TVector4<T>::operator+=(const TVector4<T> & Other) {
		this->Value[0] += Other.Value[0];
		this->Value[1] += Other.Value[1];
		this->Value[2] += Other.Value[2];
		this->Value[3] += Other.Value[3];
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T> & TVector4<T>::operator-=(const TVector4<T> & Other) {
		this->Value[0] -= Other.Value[0];
		this->Value[1] -= Other.Value[1];
		this->Value[2] -= Other.Value[2];
		this->Value[3] -= Other.Value[3];
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T> & TVector4<T>::operator*=(const TVector4<T> & Other) {
		this->Value[0] *= Other.Value[0];
		this->Value[1] *= Other.Value[1];
		this->Value[2] *= Other.Value[2];
		this->Value[3] *= Other.Value[3];
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T>& TVector4<T>::operator/=(const TVector4<T>& Other) {
		this->Value[0] /= Other.Value[0];
		this->Value[1] /= Other.Value[1];
		this->Value[2] /= Other.Value[2];
		this->Value[3] /= Other.Value[3];
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T>& TVector4<T>::operator+=(T Scalar) {
		this->Value[0] += Scalar;
		this->Value[1] += Scalar;
		this->Value[2] += Scalar;
		this->Value[3] += Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T>& TVector4<T>::operator-=(T Scalar) {
		this->Value[0] -= Scalar;
		this->Value[1] -= Scalar;
		this->Value[2] -= Scalar;
		this->Value[3] -= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T>& TVector4<T>::operator*=(T Scalar) {
		this->Value[0] *= Scalar;
		this->Value[1] *= Scalar;
		this->Value[2] *= Scalar;
		this->Value[3] *= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector4<T>& TVector4<T>::operator/=(T Scalar) {
		this->Value[0] /= Scalar;
		this->Value[1] /= Scalar;
		this->Value[2] /= Scalar;
		this->Value[3] /= Scalar;
		return *this;
	}

	template<class T>
	FORCEINLINE bool TVector4<T>::operator==(const TVector4<T> & Other) {
		return (this->Value[0] == Other.Value[0]
			&& this->Value[1] == Other.Value[1]
			&& this->Value[2] == Other.Value[2]
			&& this->Value[3] == Other.Value[3]
			);
	}

	template<class T>
	FORCEINLINE bool TVector4<T>::operator!=(const TVector4<T> & Other)
	{ return !(*this == Other); }

	template<class T>
	FORCEINLINE void TVector4<T>::operator++()
	{ ++X; ++Y; ++Z; ++W; }

	template<class T>
	FORCEINLINE void TVector4<T>::operator--()
	{ --X; --Y; --Z; --W; }

	template<class T>
	FORCEINLINE TVector4<T> & TVector4<T>::operator++(int)
	{ TVector4<T> Temp = *this; ++*this; return Temp; }

	template<class T>
	FORCEINLINE TVector4<T> & TVector4<T>::operator--(int)
	{ TVector4<T> Temp = *this; --*this; return Temp; }

	template<class T>
	FORCEINLINE T& TVector4<T>::operator[](size_t Index)
	{ return Value[Index]; }

	template<class T>
	FORCEINLINE const T& TVector4<T>::operator[](size_t Index) const
	{ return Value[Index]; }


	template<class T>
	FORCEINLINE T Length(const TVector4<T>& Vec)
	{ return sqrt(Vec.X * Vec.X + Y * Y + Z * Z + W * W); }

	template<class T>
	FORCEINLINE TVector4<T> Normalize(const TVector4<T>& Vec)
	{ return (  Vec / Length(Vec)  ); }

	template<class T>
	FORCEINLINE T Dot(const TVector4<T>& Vec1, const TVector4<T>& Vec2)
	{ return (Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z + Vec1.W * Vec2.W); }

	template<class T>
	FORCEINLINE TVector4<T> Rotate(const TVector4<T>& Vec, T Angle)
	{ return Vec; }

} }