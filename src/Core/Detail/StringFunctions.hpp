#pragma once

#include <string>

namespace Amalgamation {
	namespace Detail {


		template<class T>
		T FromString(const std::string& Value) {
			static_assert(false, "Type conversion not supported");
		}

		template<>
		int FromString<int>(const std::string& Value) { return std::stoi(Value); }

		template<>
		long FromString<long>(const std::string& Value) { return std::stol(Value); }

		template<>
		long long FromString<long long>(const std::string& Value) { return std::stoll(Value); }

		template<>
		unsigned int FromString<unsigned int>(const std::string& Value) { return std::stoul(Value); }

		template<>
		unsigned long FromString<unsigned long>(const std::string& Value) { return std::stoul(Value); }

		template<>
		unsigned long long FromString<unsigned long long>(const std::string& Value) { return std::stoull(Value); }

		template<>
		float FromString<float>(const std::string& Value) { return std::stof(Value); }

		template<>
		double FromString<double>(const std::string& Value) { return std::stod(Value); }

		template<>
		long double FromString<long double>(const std::string& Value) { return std::stold(Value); }

		template<>
		const std::string& FromString<const std::string&>(const std::string& Value) { return Value; }

		template<>
		std::string FromString<std::string>(const std::string& Value) { return Value; }

		template<>
		bool FromString<bool>(const std::string& Value) {
			if (Value == "true") {
				return true;
			}
			else {
				return false;
			}
		}

	}
}


#ifndef AE_NO_IMPL
	#include "StringFunctions.inl"
#endif