#pragma once

#include <string>

namespace Amalgamation { namespace Detail {


    template<class T>
    T FromString(const std::string& Value) {
        static_assert(true, "Type conversion not supported");
    }

    template<>
    float FromString<float>(const std::string& Value) {}


} }


#ifndef AE_NO_IMPL
    #include "StringFunctions.inl"
#endif