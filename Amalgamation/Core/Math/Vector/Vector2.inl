#include "Vector2.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	FORCEINLINE TVector2<MathType>::TVector2(MathType X, MathType Y)
		: m_Data{ X, Y } {}

	template<class MathType>
	FORCEINLINE TVector2<MathType>::TVector2(MathType Scalar)
		: m_Data{ Scalar, Scalar } {}

	template<class MathType>
	FORCEINLINE TVector2<MathType>::TVector2()
		: m_Data{ 0, 0 } {}

	template<class MathType>
	FORCEINLINE TVector2<MathType>::TVector2(const TVector2<MathType>& Other)
		: m_Data{ Other.m_Data[0], Other.m_Data[1] } {}

	template<class MathType>
	FORCEINLINE TVector2<MathType>::~TVector2()
	{}

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::Add(const TVector2<MathType>& Other) {
		this->X += Other.X;
		this->Y += Other.Y;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::Subtract(const TVector2<MathType>& Other) {
		this->X -= Other.X;
		this->Y -= Other.Y;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::Multiply(const TVector2<MathType>& Other) {
		this->X *= Other.X;
		this->Y *= Other.Y;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::Divide(const TVector2<MathType>& Other) {
		this->X /= Other.X;
		this->Y /= Other.Y;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::operator+=(const TVector2<MathType>& Other)
	{ return this->Add(Other); }

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::operator-=(const TVector2<MathType>& Other)
	{ return this->Subtract(Other); }

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::operator*=(const TVector2<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::operator/=(const TVector2<MathType>& Other)
	{ return this->Divide(Other); }

	template<class MathType>
	FORCEINLINE bool TVector2<MathType>::operator==(const TVector2<MathType>& Other)
	{ return (this->X == Other.X && this->Y == Other.Y); }

	template<class MathType>
	FORCEINLINE bool TVector2<MathType>::operator!=(const TVector2<MathType>& Other)
	{ return !(*this == Other); }

	template<class MathType>
	FORCEINLINE void TVector2<MathType>::operator++()
	{ X++; Y++; }

	template<class MathType>
	FORCEINLINE void TVector2<MathType>::operator--()
	{ X--; Y--; }

	template<class MathType>
	FORCEINLINE TVector2<MathType>& TVector2<MathType>::operator++(int)
	{ TVector2<MathType> T = *this; ++*this; return T; }

	template<class MathType>
	FORCEINLINE MathType TVector2<MathType>::operator[](size_t Index)
	{ return m_Data[Index]; }

	template<class MathType>
	FORCEINLINE MathType TVector2<MathType>::Length() {
		return sqrt(X * X + Y * Y);
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType> & TVector2<MathType>::Normalize() {
		return ((*this) /= this->Length());
	}

	template<class MathType>
	FORCEINLINE MathType TVector2<MathType>::Dot(const TVector2<MathType> & Other) {
		return (X * Other.X + Y * Other.Y);
	}


	template<class MathType>
	FORCEINLINE TVector2<MathType> & TVector2<MathType>::Rotate(MathType Angle) {
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector2<MathType> operator+(TVector2<MathType> Left, const TVector2<MathType>& Right)
	{ return Left.Add(Right); }

	template<class MathType>
	FORCEINLINE TVector2<MathType> operator-(TVector2<MathType> Left, const TVector2<MathType>& Right)
	{ return Left.Subtract(Right); }

	template<class MathType>
	FORCEINLINE TVector2<MathType> operator*(TVector2<MathType> Left, const TVector2<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector2<MathType> operator/(TVector2<MathType> Left, const TVector2<MathType>& Right)
	{ return Left.Divide(Right); }

} }