#pragma once

#include <iostream>

namespace amalgamation {

    constexpr auto& print_stream = std::cout;
    constexpr auto& error_stream = std::cerr;

    namespace ansi {
#ifdef AE_OS_LINUX
        constexpr auto red     = "\x1b[31m";
        constexpr auto green   = "\x1b[32m";
        constexpr auto yellow  = "\x1b[33m";
        constexpr auto blue    = "\x1b[34m";
        constexpr auto magenta = "\x1b[35m";
        constexpr auto cyan    = "\x1b[36m";
        constexpr auto reset   = "\x1b[0m";
#else
        constexpr auto red     = "";
        constexpr auto green   = "";
        constexpr auto yellow  = "";
        constexpr auto blue    = "";
        constexpr auto magenta = "";
        constexpr auto cyan    = "";
        constexpr auto reset   = "";
#endif
    }

    template<class... T>
    decltype(print_stream) print(T&&... args) {
        return ((print_stream << ansi::reset << "[ ]: ") << ...<< std::forward<T&&>(args));
    }

    template<class... T>
    decltype(print_stream) println(T&&... args) {
        return ((print()) << ...<< std::forward<T&&>(args)) << std::endl;
    }

    template<class... T>
    decltype(print_stream) notice(T&&... args) {
        return ((print_stream << ansi::cyan << "[-]: " << ansi::reset) << ...<< std::forward<T&&>(args));
    }

    template<class... T>
    decltype(print_stream) noticeln(T&&... args) {
        return ((notice()) << ...<< std::forward<T&&>(args)) << std::endl;
    }

    template<class... T>
    decltype(print_stream) success(T&&... args) {
        return ((print_stream << ansi::green << "[^]: " << ansi::reset) << ...<< std::forward<T&&>(args));
    }

    template<class... T>
    decltype(print_stream) successln(T&&... args) {
        return ((success()) << ...<< std::forward<T&&>(args)) << std::endl;
    }

    template<class... T>
    decltype(error_stream) warn(T&&... args) {
        return ((error_stream << ansi::yellow << "[*]: " << ansi::reset) << ...<< std::forward<T&&>(args));
    }

    template<class... T>
    decltype(error_stream) warnln(T&&... args) {
        return ((warn()) << ...<< std::forward<T&&>(args)) << std::endl;
    }

    template<class... T>
    decltype(error_stream) error(T&&... args) {
        return ((error_stream << ansi::red << "[!]: " << ansi::reset) << ...<< std::forward<T&&>(args));
    }

    template<class... T>
    decltype(error_stream) errorln(T&&... args) {
        return ((error()) << ...<< std::forward<T&&>(args)) << std::endl;
    }


}