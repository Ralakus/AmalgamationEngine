
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
	FORCEINLINE MathType TVector3<MathType>::operator[](size_t Index)
	{ return m_Data[Index]; }

	template<class MathType>
	FORCEINLINE MathType TVector3<MathType>::Length() {
		return sqrt(X * X + Y * Y + Z * Z);
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Normalize() {
		return ((*this) /= this->Length());
	}

	template<class MathType>
	FORCEINLINE MathType TVector3<MathType>::Dot(const TVector3<MathType>& Other) {
		return (X * Other.X + Y * Other.Y + Z * Other.Z);
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Rotate(MathType Angle) {
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector3<MathType>& TVector3<MathType>::Cross(const TVector3<MathType>& Other) {
		this->X = Y * Other.Z - Z * Other.Y;
		this->Y = Z * Other.X - X * Other.Z;
		this->Z = X * Other.Y - Y * Other.X;
		return *this;
	}

} }