#pragma once

#include <Core/Math/Vector/Vector4.hpp>

namespace Amalgamation {

	template<class MathType>
	class Matrix4x4 {

	private:

		TVector4<MathType> m_Data[4];

	};

}