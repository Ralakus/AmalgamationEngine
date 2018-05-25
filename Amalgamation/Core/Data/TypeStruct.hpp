#pragma once

namespace Amalgamation {

	template<class T, unsigned long Size>
	struct TypeStruct {
		T Data[Size];
		typedef T Type;
	};


	//======================================================================
	// Simple Data Vector Math Operations
	//======================================================================
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator + (const TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] + Right.Data[i];
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator - (const TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] - Right.Data[i];
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator * (const TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] * Right.Data[i];
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator / (const TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] / Right.Data[i];
		}
		return R;
	}

	// Scalar Operations

	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator + (const TypeStruct<T, Size>& Left, T Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] + Right;
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator - (const TypeStruct<T, Size>& Left, T Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] - Right;
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator * (const TypeStruct<T, Size>& Left, T Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] * Right;
		}
		return R;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator / (const TypeStruct<T, Size>& Left, T Right) {
		TypeStruct<T, Size> R;
		for (unsigned long i = 0; i < Size; i++) {
			R.Data[i] = Left.Data[i] / Right;
		}
		return R;
	}

	//======================================================================
	// Data Vector Data Modifying Math Operations
	//======================================================================
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator += (TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] += Right.Data[i];
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator -= (TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] -= Right.Data[i];
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator *= (TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] *= Right.Data[i];
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator /= (TypeStruct<T, Size>& Left, const TypeStruct<T, Size>& Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] /= Right.Data[i];
		}
		return Left;
	}

	// Scalar Operations 
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator += (TypeStruct<T, Size>& Left, T Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] += Right;
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator -= (TypeStruct<T, Size>& Left, T Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] -= Right;
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator *= (TypeStruct<T, Size>& Left, T Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] *= Right;
		}
		return Left;
	}
	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator /= (TypeStruct<T, Size>& Left, T Right) {
		for (unsigned long i = 0; i < Size; i++) {
			Left.Data[i] /= Right;
		}
		return Left;
	}

	//++ && --

	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator ++ (TypeStruct<T, Size>& Left) {
		for (unsigned long i = 0; i < Size; i++) {
			++Left[i];
		}
		return Left;
	}

	template<class T, unsigned long Size>
	TypeStruct<T, Size>& operator -- (TypeStruct<T, Size>& Left) {
		for (unsigned long i = 0; i < Size; i++) {
			--Left[i];
		}
		return Left;
	}

	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator ++ (TypeStruct<T, Size>& Left, int) {
		TypeStruct<T, Size> TVec = Left;
		++TVec;
		return TVec;
	}

	template<class T, unsigned long Size>
	TypeStruct<T, Size> operator -- (TypeStruct<T, Size>& Left, int) {
		TypeStruct<T, Size> TVec = Left;
		--TVec;
		return TVec;
	}
}