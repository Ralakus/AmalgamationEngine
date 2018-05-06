#pragma once

#include <LinearMath/btVector3.h>
#include <Core/Lua/LuaState.hpp>

namespace Amalgamation { namespace Math {

	template<class MathType>
	class TVector3 {

		using TVec3 = TVector3<MathType>;

	public:

		union {

			MathType m_Data[3];
			MathType X, Y, Z;

		};

		TVector3(MathType X, MathType Y, MathType Z) : m_Data{ X, Y, Z }
		{}

		TVector3(MathType Scalar) : m_Data{ Scalar, Scalar, Scalar }
		{}

		TVector3() : m_Data{ 0,0,0 }
		{}

		TVector3(const TVec3& Other) : m_Data{ Other.m_Data[0], Other.m_Data[1], Other.m_Data[2] }
		{}

		TVector3(const btVector3& btVec) : m_Data{ btVec.x, btVec.y, btVec.z }
		{}

		void operator = (const TVec3& Other) {
			memcpy(&m_data, &Other.m_Data, sizeof(MathType) * 3);
		}

		~TVector3() {}

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

		btVector3 BT() const { return btVector3(X, Y, Z); }

		REGISTER_TO_LUA_STACK(
			LuaState::GetAENamespace().new_usertype<TVector3<float>>("Vector3"

				"X", TVector3<float>::X,
				"Y", TVector3<float>::Y,
				"Z", TVector3<float>::Z

			);
		);

	};

	template<class MathType>
	using TVec3 = TVector3<MathType>;

	using Vec3    = TVec3<float>;
	using Vector3 =  Vec3;

} }