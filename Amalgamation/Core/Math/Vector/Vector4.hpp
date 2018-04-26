#pragma once

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector4 {

		using TVec4 = TVector4<MathType>;

	public:

		union {

			MathType m_Data[4];
			MathType X, Y, Z, W;

		};

		TVector4(MathType X, MathType Y, MathType Z, MathType W) : m_Data{ X, Y, Z, W }
		{}

		TVector4(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar }
		{}

		TVector4() : m_Data{ 0, 0, 0, 0 }
		{}

		TVector4(const TVec4& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2], Other.m_Data[3] }
		{}

		void operator = (const TVec4& Other) {

			m_Data[0] = Other.m_Data[0];
			m_Data[1] = Other.m_Data[1];
			m_Data[2] = Other.m_Data[2];
			m_Data[3] = Other.m_Data[3];
		}

		~TVector3() {}

		TVec4& Add(const TVec4& Other) {
			this->m_Data[0] += Other.m_Data[0];
			this->m_Data[1] += Other.m_Data[1];
			this->m_Data[2] += Other.m_Data[2];
			this->m_Data[3] += Other.m_Data[3];
			return *this;
		}

		TVec4& Subtract(const TVec4& Other) {
			this->m_Data[0] -= Other.m_Data[0];
			this->m_Data[1] -= Other.m_Data[1];
			this->m_Data[2] -= Other.m_Data[2];
			this->m_Data[3] -= Other.m_Data[3];
			return *this;
		}

		TVec4& Multiply(const TVec4& Other) {
			this->m_Data[0] *= Other.m_Data[0];
			this->m_Data[1] *= Other.m_Data[1];
			this->m_Data[2] *= Other.m_Data[2];
			this->m_Data[3] *= Other.m_Data[3];
			return *this;
		}

		TVec4& Divide(const TVec4& Other) {
			this->m_Data[0] /= Other.m_Data[0];
			this->m_Data[1] /= Other.m_Data[1];
			this->m_Data[2] /= Other.m_Data[2];
			this->m_Data[3] /= Other.m_Data[3];
			return *this;
		}

		friend TVec4 operator+(TVec4 Left, const TVec4& Right) { return Left.Add(Right); }
		friend TVec4 operator-(TVec4 Left, const TVec4& Right) { return Left.Subtract(Right); }
		friend TVec4 operator*(TVec4 Left, const TVec4& Right) { return Left.Multiply(Right); }
		friend TVec4 operator/(TVec4 Left, const TVec4& Right) { return Left.Divide(Right); }

		TVec4& operator+=(const TVec4& Other) { return this->Add(Other); }
		TVec4& operator-=(const TVec4& Other) { return this->Subtract(Other); }
		TVec4& operator*=(const TVec4& Other) { return this->Multiply(Other); }
		TVec4& operator/=(const TVec4& Other) { return this->Divide(Other); }

		bool operator==(const TVec4& Other) { 
			return (this->m_Data[0] == Other.m_Data[0]
				 && this->m_Data[1] == Other.m_Data[1]
				 && this->m_Data[2] == Other.m_Data[2]
				 && this->m_Data[3] == Other.m_Data[3]
			);
		}
		bool operator!=(const TVec4& Other) { return !(*this == Other); }

		void operator++() { m_Data[0]++; m_Data[1]++; m_Data[2]++; m_Data[3]++; }
		void operator--() { m_Data[0]--; m_Data[1]--; m_Data[2]--; m_Data[3]--; }

	};

	template<class MathType>
	using TVec4 = TVector3<MathType>;

	using Vec4 = TVec4<float>;
	using Vector4 = Vec4;

} }