#pragma once
#include "../Platform/Platform.hpp"

#if   defined(AE_LINUX)

    #define RST  "\x1B[0m"
    #define KRED  "\x1B[31m"
    #define KGRN  "\x1B[32m"
    #define KYEL  "\x1B[33m"
    #define KBLU  "\x1B[34m"
    #define KMAG  "\x1B[35m"
    #define KCYN  "\x1B[36m"
    #define KWHT  "\x1B[37m"

    #define FRED(x) KRED x RST
    #define FGRN(x) KGRN x RST
    #define FYEL(x) KYEL x RST
    #define FBLU(x) KBLU x RST
    #define FMAG(x) KMAG x RST
    #define FCYN(x) KCYN x RST
    #define FWHT(x) KWHT x RST

    #define BOLD(x) "\x1B[1m" x RST
    #define UNDL(x) "\x1B[4m" x RST

    #define AE_LOG(x)         printf("%s %s%s%s\n", FWHT(AE_LOG_STR),         KWHT, x, RST)
    #define AE_LOG_NOTE(x)    printf("%s %s%s%s\n", FBLU(AE_LOG_NOTE_STR),    KBLU, x, RST)
    #define AE_LOG_ERROR(x)   printf("%s %s%s%s\n", FRED(AE_LOG_ERROR_STR),   KRED, x, RST)
    #define AE_LOG_WARNING(x) printf("%s %s%s%s\n", FYEL(AE_LOG_WARNING_STR), KYEL, x, RST)
    #define AE_LOG_SUCCESS(x) printf("%s %s%s%s\n", FGRN(AE_LOG_SUCCESS_STR), KGRN, x, RST)

	#define AE_LOG_COLOR_RESET RST
	#define AE_LOG_TEXT_COLOR KWHT
	#define AE_LOG_NOTE_COLOR KBLU
	#define AE_LOG_WARNING_COLOR KYEL
	#define AE_LOG_ERROR_COLOR KRED
	#define AE_LOG_SUCCESS_COLOR KGRN

#elif defined(AE_WINDOWS)

    #include <windows.h>

    #define WIN_CON_COL(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    #define WIN_CON_RES        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    #define AE_LOG(x)         WIN_CON_RES;     printf("%s %s\n", AE_LOG_STR,         x); WIN_CON_RES
    #define AE_LOG_NOTE(x)    WIN_CON_COL(11); printf("%s %s\n", AE_LOG_NOTE_STR,    x); WIN_CON_RES
    #define AE_LOG_ERROR(x)   WIN_CON_COL(12); printf("%s %s\n", AE_LOG_ERROR_STR,   x); WIN_CON_RES
    #define AE_LOG_WARNING(x) WIN_CON_COL(14); printf("%s %s\n", AE_LOG_WARNING_STR, x); WIN_CON_RES
    #define AE_LOG_SUCCESS(x) WIN_CON_COL(10); printf("%s %s\n", AE_LOG_SUCCESS_STR, x); WIN_CON_RES

	#define AE_LOG_COLOR_RESET WIN_CON_RES
	#define AE_LOG_TEXT_COLOR WIN_CON_RES
	#define AE_LOG_NOTE_COLOR WIN_CON_COL(11);
	#define AE_LOG_WARNING_COLOR WIN_CON_COL(14);
	#define AE_LOG_ERROR_COLOR WIN_CON_COL(12);
	#define AE_LOG_SUCCESS_COLOR WIN_CON_COL(10);

#endif // AE_LINUX

#include <iostream>

namespace Amalgamation {


	class Log {

	public:
#if   defined(AE_LINUX)

		template<class T>
		static void Text(const T& Message) {
			std::cout << AE_LOG_TEXT_COLOR << AE_LOG_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
		}

		template<class T>
		static void Note(const T& Message) {
			std::cout << AE_LOG_NOTE_COLOR << AE_LOG_NOTE_STR << " " <<  Message << AE_LOG_COLOR_RESET << '\n';
		}

		template<class T>
		static void Warning(const T& Message) {
			std::cout << AE_LOG_WARNING_COLOR << AE_LOG_WARNING_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
		}

		template<class T>
		static void Error(const T& Message) {
			std::cout << AE_LOG_ERROR_COLOR << AE_LOG_ERROR_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
		}

		template<class T>
		static void Success(const T& Message) {
			std::cout << AE_LOG_SUCCESS_COLOR << AE_LOG_SUCCESS_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
		}

#elif defined(AE_WINDOWS)

		template<class T>
		static void Text(const T& Message) {
			AE_LOG_TEXT_COLOR std::cout << AE_LOG_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
		}

		template<class T>
		static void Note(const T& Message) {
			AE_LOG_NOTE_COLOR std::cout << AE_LOG_NOTE_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
		}

		template<class T>
		static void Warning(const T& Message) {
			AE_LOG_WARNING_COLOR std::cout << AE_LOG_WARNING_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
		}

		template<class T>
		static void Error(const T& Message) {
			AE_LOG_ERROR_COLOR std::cout << AE_LOG_ERROR_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
		}

		template<class T>
		static void Success(const T& Message) {
			AE_LOG_SUCCESS_COLOR std::cout << AE_LOG_SUCCESS_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
		}

#endif

	};


}