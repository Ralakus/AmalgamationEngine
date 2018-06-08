
namespace Amalgamation { namespace Math {

	template<class T>
	FORCEINLINE TVector2<T>::TVector2(T X, T Y)
		: Value{ X, Y } {}

	template<class T>
	FORCEINLINE TVector2<T>::TVector2(T Scalar)
		: Value{ Scalar, Scalar } {}

	template<class T>
	FORCEINLINE TVector2<T>::TVector2()
		: Value{ 0, 0 } {}

	template<class T>
	FORCEINLINE TVector2<T>::TVector2(const TVector2<T>& Other)
		: Value{ Other.Value[0], Other.Value[1] } {}

	template<class T>
	FORCEINLINE TVector2<T>::~TVector2()
	{}

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator+=(const TVector2<T>& Other) {
		this->X += Other.X;
		this->Y += Other.Y;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator-=(const TVector2<T>& Other) {
		this->X -= Other.X;
		this->Y -= Other.Y;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator*=(const TVector2<T>& Other) {
		this->X *= Other.X;
		this->Y *= Other.Y;
		return *this;
	}

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator/=(const TVector2<T>& Other) {
		this->X /= Other.X;
		this->Y /= Other.Y;
		return *this;
	}

	template<class T>
	FORCEINLINE bool TVector2<T>::operator==(const TVector2<T>& Other)
	{ return (this->X == Other.X && this->Y == Other.Y); }

	template<class T>
	FORCEINLINE bool TVector2<T>::operator!=(const TVector2<T>& Other)
	{ return !(*this == Other); }

	template<class T>
	FORCEINLINE void TVector2<T>::operator++()
	{ X++; Y++; }

	template<class T>
	FORCEINLINE void TVector2<T>::operator--()
	{ X--; Y--; }

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator++(int)
	{ TVector2<T> Temp = *this; ++*this; return Temp; }

	template<class T>
	FORCEINLINE TVector2<T>& TVector2<T>::operator--(int)
	{ TVector2<T> Temp = *this; --*this; return Temp; }

	template<class T>
	FORCEINLINE T& TVector2<T>::operator[](size_t Index)
	{ return Value[Index]; }

	template<class T>
	FORCEINLINE const T& TVector2<T>::operator[](size_t Index) const
	{ return Value[Index]; }






	template<class T>
	FORCEINLINE TVector2<T> operator+(TVector2<T> Left, const TVector2<T>& Right)
	{ return Left += Right; }

	template<class T>
	FORCEINLINE TVector2<T> operator-(TVector2<T> Left, const TVector2<T>& Right)
	{ return Left -= Right; }

	template<class T>
	FORCEINLINE TVector2<T> operator*(TVector2<T> Left, const TVector2<T>& Right)
	{ return Left *= Right; }

	template<class T>
	FORCEINLINE TVector2<T> operator/(TVector2<T> Left, const TVector2<T>& Right)
	{ return Left /= Right; }






	template<class T>
	FORCEINLINE T Length(const TVector2<T>& Vec) {
		return sqrt(Vec.X * Vec.X + Vec.Y * Vec.Y);
	}

	template<class T>
	FORCEINLINE TVector2<T> Normalize(const TVector2<T>& Vec)
	{ return  ( Vec / Length(Vec)  ); }

	template<class T>
	FORCEINLINE T Dot(const TVector2<T>& Vec1, const TVector2<T>& Vec2)
	{ return (Vec1.X * Vec2.X + Vec1.Y * Vec2.Y); }

	template<class T>
	FORCEINLINE TVector2<T> Rotate(const TVector2<T>& Vec, T Angle)
	{ return Vec; }

} }