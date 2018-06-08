
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
	FORCEINLINE MathType Length(const TVector4<MathType>& Vec)
	{ return sqrt(Vec.X * Vec.X + Y * Y + Z * Z + W * W); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> Normalize(const TVector4<MathType>& Vec)
	{ return (  Vec / Length(Vec)  ); }

	template<class MathType>
	FORCEINLINE MathType Dot(const TVector4<MathType>& Vec1, const TVector4<MathType>& Vec2)
	{ return (Vec1.X * Vec2.X + Vec1.Y * Vec2.Y + Vec1.Z * Vec2.Z + Vec1.W * Vec2.W); }

	template<class MathType>
	FORCEINLINE TVector4<MathType> Rotate(const TVector4<MathType>& Vec, MathType Angle)
	{ return Vec; }

} }