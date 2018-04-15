#pragma once

#include <LinearMath/btVector3.h>

namespace Amalgamation {

	template<class MathType>
	class TVector3 {

		using TVec3 = TVector3<MathType>;

		MathType m_Data[3];

	public:

		TVector3(MathType X, MathType Y, MathType Z) : m_Data{ X, Y, Z },
			X(m_Data[0]), Y(m_Data[1]), Z(m_Data[2]) {}

		TVector3(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar },
			X(m_Data[0]), Y(m_Data[1]), Z(m_Data[2]) {}

		TVector3() : m_Data{ 0,0,0 },
			X(m_Data[0]), Y(m_Data[1]), Z(m_Data[2]) {}

		TVector3(const TVec3& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2] },
			X(m_Data[0]), Y(m_Data[1]), Z(m_Data[2]) {}

		TVector3(const btVector3& btVec) : m_Data{ btVec.x, btVec.y, btVec.z },
			X(m_Data[0]), Y(m_Data[1]), Z(m_Data[2]) {}

		void operator = (const TVec3& Other) {

			m_Data[0] = Other.m_Data[0];
			m_Data[1] = Other.m_Data[1];
			m_Data[2] = Other.m_Data[2];

			X = m_Data[0];
			Y = m_Data[1];
			Z = m_Data[2];
		}

		~TVector3() {}

		MathType &X, &Y, &Z;

		TVec3& Add(const TVec3& Other) {
			this->m_Data[0] += Other.m_Data[0];
			this->m_Data[1] += Other.m_Data[1];
			this->m_Data[2] += Other.m_Data[2];
			return *this;
		}

		TVec3& Subtract(const TVec3& Other) {
			this->m_Data[0] -= Other.m_Data[0];
			this->m_Data[1] -= Other.m_Data[1];
			this->m_Data[2] -= Other.m_Data[2];
			return *this;
		}

		TVec3& Multiply(const TVec3& Other) {
			this->m_Data[0] *= Other.m_Data[0];
			this->m_Data[1] *= Other.m_Data[1];
			this->m_Data[2] *= Other.m_Data[2];
			return *this;
		}

		TVec3& Divide(const TVec3& Other) {
			this->m_Data[0] /= Other.m_Data[0];
			this->m_Data[1] /= Other.m_Data[1];
			this->m_Data[2] /= Other.m_Data[2];
			return *this;
		}

		friend TVec3 operator+(TVec3 Left, const TVec3& Right) { return Left.Add(Right); }
		friend TVec3 operator-(TVec3 Left, const TVec3& Right) { return Left.Subtract(Right); }
		friend TVec3 operator*(TVec3 Left, const TVec3& Right) { return Left.Multiply(Right); }
		friend TVec3 operator/(TVec3 Left, const TVec3& Right) { return Left.Divide(Right); }

		TVec3& operator+=(const TVec3& Other) { return this->Add(Other); }
		TVec3& operator-=(const TVec3& Other) { return this->Subtract(Other); }
		TVec3& operator*=(const TVec3& Other) { return this->Multiply(Other); }
		TVec3& operator/=(const TVec3& Other) { return this->Divide(Other); }

		bool operator==(const TVec3& Other) { return (this->m_Data[0] == Other.m_Data[0] && this->m_Data[1] == Other.m_Data[1] && this->m_Data[2] == Other.m_Data[2]); }
		bool operator!=(const TVec3& Other) { return !(*this == Other); }

		void operator++() { m_Data[0]++; m_Data[1]++; m_Data[2]++; }
		void operator--() { m_Data[0]--; m_Data[1]--; m_Data[2]--; }

		btVector3 TobtVec() const { return btVector3(X, Y, Z); }

	};

	template<class MathType>
	using TVec3 = TVector3<MathType>;

	using Vec3    = TVec3<float>;
	using Vector3 =  Vec3;

}