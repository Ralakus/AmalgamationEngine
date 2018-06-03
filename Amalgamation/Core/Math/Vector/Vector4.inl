
namespace Amalgamation { namespace Math {

	template<class MathType>
	template<class ...EXArgs>
	FORCEINLINE TVector4<MathType>::TVector4(MathType X, MathType Y, MathType Z, MathType W, EXArgs && ...Ex)
		: m_Data{ X, Y, Z, W } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4(MathType X, MathType Y, MathType Z, MathType W)
		: m_Data{ X, Y, Z, W } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4(MathType X, MathType Y, MathType Z)
		: m_Data{ X, Y, Z, 0 } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4(MathType X, MathType Y)
		: m_Data{ X, Y, 0, 0 } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4(MathType Scalar)
		: m_Data{ Scalar, Scalar, Scalar } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4()
		: m_Data{ 0, 0, 0, 0 } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::TVector4(const TVector4<MathType> & Other)
		: m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] } {}

	template<class MathType>
	FORCEINLINE TVector4<MathType>::~TVector4()
	{}

	template<class MathType>
	FORCEINLINE TVector4<MathType>& TVector4<MathType>::Add(const TVector4<MathType> & Other) {
		this->m_Data[0] += Other.m_Data[0];
		this->m_Data[1] += Other.m_Data[1];
		this->m_Data[2] += Other.m_Data[2];
		this->m_Data[3] += Other.m_Data[3];
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::Subtract(const TVector4<MathType> & Other) {
		this->m_Data[0] -= Other.m_Data[0];
		this->m_Data[1] -= Other.m_Data[1];
		this->m_Data[2] -= Other.m_Data[2];
		this->m_Data[3] -= Other.m_Data[3];
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::Multiply(const TVector4<MathType> & Other) {
		this->m_Data[0] *= Other.m_Data[0];
		this->m_Data[1] *= Other.m_Data[1];
		this->m_Data[2] *= Other.m_Data[2];
		this->m_Data[3] *= Other.m_Data[3];
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::Divide(const TVector4<MathType> & Other) {
		this->m_Data[0] /= Other.m_Data[0];
		this->m_Data[1] /= Other.m_Data[1];
		this->m_Data[2] /= Other.m_Data[2];
		this->m_Data[3] /= Other.m_Data[3];
		return *this;
	}

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::operator+=(const TVector4<MathType> & Other)
	{ return this->Add(Other); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::operator-=(const TVector4<MathType> & Other)
	{ return this->Subtract(Other); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::operator*=(const TVector4<MathType> & Other)
	{ return this->Multiply(Other); }

	template<class MathType>
	FORCEINLINE TVector4<MathType>& TVector4<MathType>::operator/=(const TVector4<MathType>& Other)
	{ return this->Divide(Other); }

	template<class MathType>
	FORCEINLINE bool TVector4<MathType>::operator==(const TVector4<MathType> & Other) {
		return (this->m_Data[0] == Other.m_Data[0]
			&& this->m_Data[1] == Other.m_Data[1]
			&& this->m_Data[2] == Other.m_Data[2]
			&& this->m_Data[3] == Other.m_Data[3]
			);
	}

	template<class MathType>
	FORCEINLINE bool TVector4<MathType>::operator!=(const TVector4<MathType> & Other)
	{ return !(*this == Other); }

	template<class MathType>
	FORCEINLINE void TVector4<MathType>::operator++()
	{ ++X; ++Y; ++Z; ++W; }

	template<class MathType>
	FORCEINLINE void TVector4<MathType>::operator--()
	{ --X; --Y; --Z; --W; }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::operator++(int)
	{ TVector4<MathType> T = *this; ++*this; return T; }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::operator--(int)
	{ TVector4<MathType> T = *this; --*this; return T; }

	template<class MathType>
	FORCEINLINE MathType& TVector4<MathType>::operator[](size_t Index)
	{ return m_Data[Index]; }

	template<class MathType>
	FORCEINLINE const MathType& TVector4<MathType>::operator[](size_t Index) const
	{ return m_Data[Index]; }

	template<class MathType>
	FORCEINLINE MathType TVector4<MathType>::Length()
	{ return sqrt(X * X + Y * Y + Z * Z + W * W); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::Normalize()
	{ return ((*this) /= this->Length()); }

	template<class MathType>
	FORCEINLINE MathType TVector4<MathType>::Dot(const TVector4<MathType> & Other)
	{ return (X * Other.X + Y * Other.Y + Z * Other.Z + W * Other.W); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> & TVector4<MathType>::Rotate(MathType Angle)
	{ return *this; }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator+(TVector4<MathType> Left, const TVector4<MathType> & Right)
	{ return Left.Add(Right); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator-(TVector4<MathType> Left, const TVector4<MathType> & Right)
	{ return Left.Subtract(Right); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator*(TVector4<MathType> Left, const TVector4<MathType> & Right)
	{ return Left.Multiply(Right); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> operator/(TVector4<MathType> Left, const TVector4<MathType> & Right)
	{ return Left.Divide(Right); }

} }