#pragma once

#include "osdef.hpp"

#define NON_COPYABLE(Class) Class(const Class& Other) = delete; 
#define SINGLETON_INSTANCE(Class) NON_COPYABLE(Class) static Class& Instance() { static Class m_Instance; return m_Instance; }

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