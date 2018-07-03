#pragma once

using uint64 = unsigned long long int;
using uint32 = unsigned           int;
using uint16 = unsigned short     int;
using uint8  = unsigned char;

using int64  = signed long long int;
using int32  = signed           int;
using int16  = signed short     int;
using int8   = signed char;

using float32 = float;
using float64 = double;

using Byte = uint8;

#include "OSDefines.hpp"

#ifdef AE_COMPILER_MSVC
	#define FORCEINLINE __forceinline
	#define FORCENOINLINE __declspec(noinline)
#elif defined(AE_COMPILER_GCC) || defined(AE_COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
	#define FORCENOINLINE __attribute__(( noinline ))
#else
	#define FORCEINLINE inline
	#define FORCENOINLINE
#endif

#define SafeDelete(x)   { if(x) { delete x; x = nullptr; } }
#define SafeDeleteArr(x) { if(x) { delete[] x; x = nullptr; } }

namespace Amalgamation {
	template<class Type>
	struct IsPointer { static const bool Value = false; };
	template<class Type>
	struct IsPointer<Type*> { static const bool Value = true; };

	template<class Type1, class Type2>
	struct IsEqual { static const bool Value = false; };
	template<class Type>
	struct IsEqual<Type, Type> { static const bool Value = true; };

	class ID {
	public:
		static uint64 GetUnique() {
			static uint64 m_ID = 0;
			return ++m_ID;
		}
	};
}
