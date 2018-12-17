#pragma once

#include "../Platform/HelperMacros.hpp"
#include "MathDefines.hpp"

namespace Amalgamation { namespace Math {
	template<class T>
	FORCEINLINE T Lerp(const T& Value1, const T& Value2, float Weight) {
		return (1 - Weight) * Value1 + Weight * Value2;
	}
    template<class T>
    FORCEINLINE T Radians(const T& Degrees){
        return Degrees * (AE_TAU / 360);
    }
    template<class T>
    FORCEINLINE T Degrees(const T& Radians){
        return Radians * (360 / AE_TAU);
    }
} }