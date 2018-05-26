#pragma once

#include "../Platform/Platform.hpp"
#include "MathDefines.hpp"

namespace Amalgamation { namespace Math {
	template<class Type>
	FORCEINLINE Type Lerp(const Type& Value1, const Type& Value2, float Weight) {
		return (1 - Weight) * Value1 + Weight * Value2;
	}
    template<class Type>
    FORCEINLINE Type Radians(const Type& Degrees){
        return Degrees * (AE_PI / 180);
    }
    template<class Type>
    FORCEINLINE Type Degrees(const Type& Radians){
        return Radians * (180 / AE_PI);
    }
} }
