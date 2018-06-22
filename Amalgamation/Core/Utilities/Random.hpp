#pragma once

#include "../Platform/Platform.hpp"
#include <string>
#include <time.h>

namespace Amalgamation{

    class Random{
    public:

		FORCEINLINE static std::string Name(size_t MinLength, size_t MaxLength);

		FORCEINLINE static size_t Uint(size_t Min, size_t Max);

		FORCEINLINE static int Int(int Min, int Max);

		FORCEINLINE static bool RandomizeOnce(bool Reset = false);

    };

}

#include "Random.inl"