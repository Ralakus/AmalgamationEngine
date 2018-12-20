#pragma once

#if defined(__linux__)
    #define AE_LINUX
#elif defined(_WIN32) || defined(_WIN64)
    #define AE_WINDOWS
#elif defined(__APPLE__)
    #define AE_APPLE
#elif defined(BSD)
    #define AE_BSD
#endif // __linux__

#if defined(__clang__)
    #define AE_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define AE_COMPILER_GCC
#elif defined(_MSC_VER)
    #define AE_COMPILER_MSVC
#else
    #define AE_COMPILER_OTHER
#endif