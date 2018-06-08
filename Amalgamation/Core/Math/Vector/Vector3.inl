#include "../Quaternion/Quaternion.hpp"
#include "Vector3.hpp"

namespace Amalgamation { namespace Math {

	template<class MathType>
	template<class ...EXArgs>
	FORCEINLINE TVector3<MathType>::TVector3(MathType X, MathType Y, MathType Z, EXArgs && ...Ex)
		: m_Data{ X, Y, Z } {}

	template<class MathType>
	FORCEINLINE Amalgamation::Math::TVector3<MathType>::TVector3(MathType X, MathType Y, MathType Z)
		: m_Data{ X, Y, Z } {}

	template<class MathType>
	FORCEINLINE TVector3<MathType>::TVector3(MathType X, MathType Y)
		: m_Data{ X, Y, 0 } {}

	template<class MathType>
	FORCEINLINE TVector3<MathType>::TVector3(MathType Scalar)
		: m_Data{ Scalar, Scalar, Scalar } {}

	template<class MathType>
	FORCEINLINE TVector3<MathType>::TVector3()
		: m_Data{ 0, 0, 0 } {}

	template<class MathType>
	FORCEINLINE TVector3<MathType>::TVector3(const TVector3<MathType> & Other)
		: m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2] } {}

	template<class MathType>
	FORCEINLINE TVector3<MathType>::~TVector3()
	{}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& Amalgamation::Math::TVector3<MathType>::Add(const TVector3<MathType>& Other) {
		this->X += Other.X;
		this->Y += Other.Y;
		this->Z += Other.Z;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Subtract(const TVector3<MathType>& Other) {
		this->X -= Other.X;
		this->Y -= Other.Y;
		this->Z -= Other.Z;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Multiply(const TVector3<MathType>& Other) {
		this->X *= Other.X;
		this->Y *= Other.Y;
		this->Z *= Other.Z;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Divide(const TVector3<MathType>& Other) {
		this->X /= Other.X;
		this->Y /= Other.Y;
		this->Z /= Other.Z;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Add(MathType Scalar) {
		this->X += Scalar;
		this->Y += Scalar;
		this->Z += Scalar;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Subtract(MathType Scalar) {
		this->X -= Scalar;
		this->Y -= Scalar;
		this->Z -= Scalar;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Multiply(MathType Scalar) {
		this->X *= Scalar;
		this->Y *= Scalar;
		this->Z *= Scalar;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Divide(MathType Scalar) {
		this->X /= Scalar;
		this->Y /= Scalar;
		this->Z /= Scalar;
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Multiply(const TQuaternion<MathType>& Other){
		return ((*this) = Other.RotateVec(*this));
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator+(TVector3<MathType> Left, const TVector3<MathType>& Right)
	{ return Left.Add(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator-(TVector3<MathType> Left, const TVector3<MathType>& Right)
	{ return Left.Subtract(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator*(TVector3<MathType> Left, const TVector3<MathType>& Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator/(TVector3<MathType> Left, const TVector3<MathType>& Right)
	{ return Left.Divide(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator+(TVector3<MathType> Left, MathType Scalar)
	{ return Left.Multiply(Scalar); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator-(TVector3<MathType> Left, MathType Scalar) 
	{ return Left.Subtract(Scalar); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator*(TVector3<MathType> Left, MathType Scalar) 
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> operator/(TVector3<MathType> Left, MathType Scalar) 
	{ return Left.Divide(Scalar); }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator+=(const TVector3<MathType>& Other)
	{ return this->Add(Other); }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator-=(const TVector3<MathType>& Other)
	{ return this->Subtract(Other); }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator*=(const TVector3<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator/=(const TVector3<MathType>& Other)
	{ return this->Divide(Other); }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator*=(const TQuaternion<MathType>& Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE bool TVector3<MathType>::operator==(const TVector3<MathType>& Other)
	{ return (this->X == Other.X && this->Y == Other.Y && this->Z == Other.Z); }

	template<class MathType>
	FORCEINLINE bool TVector3<MathType>::operator!=(const TVector3<MathType>& Other)
	{ return !(*this == Other); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> TVector3<MathType>::operator++()
	{ X++; Y++; Z++; return *this; }

	template<class MathType>
	FORCEINLINE TVector3<MathType> TVector3<MathType>::operator--()
	{ X--; Y--; Z--; return *this; }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator++(int)
	{ TVector3<MathType> T = *this; ++*this; return T; }

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::operator--(int)
	{ TVector3<MathType> T = *this; --*this; return T; }

	template<class MathType>
	FORCEINLINE MathType& TVector3<MathType>::operator[](size_t Index)
	{ return m_Data[Index]; }

	template<class MathType>
	FORCEINLINE const MathType & TVector3<MathType>::operator[](size_t Index) const
	{ return m_Data[Index]; }


	template<class MathType>
	FORCEINLINE MathType Length(const TVector3<MathType>& Vec)
	{ return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> Normalize(const TVector3<MathType>& Vec)
	{ return (  Vec / Length(Vec)  ); }

	template<class MathType>
	FORCEINLINE MathType Dot(const TVector3<MathType>& Vec1, const TVector3<MathType>& Vec2)
	{ return (Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z); }

	template<class MathType>
	FORCEINLINE TVector3<MathType> Rotate(const TVector3<MathType>& Vec, MathType Angle)
	{ return Vec; }

	template<class MathType>
	FORCEINLINE TVector3<MathType> Cross(const TVector3<MathType>& Vec1, const TVector3<MathType>& Vec2) {
		return {
			Vec1.Y * Vec2.Z - Vec1.Z * Vec2.Y,
			Vec1.Z * Vec2.X - Vec1.X * Vec2.Z,
			Vec1.X * Vec2.Y - Vec1.Y * Vec2.X,
		};
	}


} }