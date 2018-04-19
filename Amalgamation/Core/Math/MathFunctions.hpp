#pragma once

namespace Amalgamation { namespace Math {
	template<class Type>
	Type Lerp(const Type& Value1, const Type& Value2, float Weight) {
		return (1 - Weight) * Value1 + Weight * Value2;
	}
} }