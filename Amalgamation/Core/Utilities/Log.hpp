#pragma once

#include "../Platform/OSDefines.hpp"

#define AE_LOG_NOTE_STR    "[LOG_NOTE]:"
#define AE_LOG_ERROR_STR   "[LOG_ERROR]:"
#define AE_LOG_WARNING_STR "[LOG_WARNING]:"
#define AE_LOG_SUCCESS_STR "[LOG_SUCCESS]:"
#define AE_LOG_STR         "[LOG]:"

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
#include <vector>

namespace Amalgamation {


	class Log {

	public:

		struct Color {
			Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}
			float R, G, B, A;
		};

		static bool& IsEnabled() { static bool m_Enabled = true; return m_Enabled; }

		static std::vector<std::pair<Color, std::string>>& GetBuffer() { static std::vector<std::pair<Color, std::string>> m_Buffer; return m_Buffer; }

#if   defined(AE_LINUX)

		
		static void Text(const std::string& Message) {
			if (IsEnabled()) {
				std::cout << AE_LOG_TEXT_COLOR << AE_LOG_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 1.f, 1.f, 1.f), Message);
			}
		}

		
		static void Note(const std::string& Message) {
			if (IsEnabled()) {
				std::cout << AE_LOG_NOTE_COLOR << AE_LOG_NOTE_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
			}
			else {
				GetBuffer().emplace_back(Color(0.1f, 0.1f, 1.f, 1.f), Message);
			}
		}

		
		static void Warning(const std::string& Message) {
			if (IsEnabled()) {
				std::cout << AE_LOG_WARNING_COLOR << AE_LOG_WARNING_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 1.f, 0.f, 1.f ), Message);
			}
		}

		
		static void Error(const std::string& Message) {
			if (IsEnabled()) {
				std::cout << AE_LOG_ERROR_COLOR << AE_LOG_ERROR_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 0.1f, 0.1f, 1.f), Message);
			}
		}

		
		static void Success(const std::string& Message) {
			if (IsEnabled()) {
				std::cout << AE_LOG_SUCCESS_COLOR << AE_LOG_SUCCESS_STR << " " << Message << AE_LOG_COLOR_RESET << '\n';
			}
			else {
				GetBuffer().emplace_back(Color(0.1f, 1.f, 0.1f, 1.f), Message);
			}
		}

#elif defined(AE_WINDOWS)

		
		static void Text(const std::string& Message) {
			if (IsEnabled()) {
				AE_LOG_TEXT_COLOR std::cout << AE_LOG_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 1.f, 1.f, 1.f), Message);
			}
		}

		
		static void Note(const std::string& Message) {
			if (IsEnabled()) {
				AE_LOG_NOTE_COLOR std::cout << AE_LOG_NOTE_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
			}
			else {
				GetBuffer().emplace_back(Color( 0.1f, 0.1f, 1.f, 1.f ), Message);
			}
		}

		
		static void Warning(const std::string& Message) {
			if (IsEnabled()) {
				AE_LOG_WARNING_COLOR std::cout << AE_LOG_WARNING_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 1.f, 0.f, 1.f ), Message);
			}
		}

		
		static void Error(const std::string& Message) {
			if (IsEnabled()) {
				AE_LOG_ERROR_COLOR std::cout << AE_LOG_ERROR_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
			}
			else {
				GetBuffer().emplace_back(Color(1.f, 0.1f, 0.1f, 1.f ), Message);
			}
		}

		
		static void Success(const std::string& Message) {
			if (IsEnabled()) {
				AE_LOG_SUCCESS_COLOR std::cout << AE_LOG_SUCCESS_STR << " " << Message << '\n'; AE_LOG_COLOR_RESET
			}
			else {
				GetBuffer().emplace_back(Color(0.1f, 1.f, 0.1f, 1.f ), Message);
			}
		}

#endif

	};


}