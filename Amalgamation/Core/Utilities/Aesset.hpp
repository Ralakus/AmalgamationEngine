#pragma once

#include "File.hpp"
#include "Log.hpp"
#include <string>

namespace Amalgamation {

	class Aesset {

		/*

		======
		FORMAT
		======

		<PropertyName/PropertyValue>

		< = Opening statement
		/ = Value   definition
		> = Closing statement

		*/

		File m_File;
		std::string m_Content;

		mutable std::string m_Buffer;

	public:

		static std::string ReadError();

		FORCEINLINE Aesset();
		FORCEINLINE Aesset(const std::string& Data, bool IsFile = true, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);
		~Aesset();

		FORCEINLINE void LoadFile(const std::string& Name, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);

		FORCEINLINE void LoadDataString(const std::string& Data);

		FORCEINLINE void Unload();

		FORCEINLINE const std::string& GetData() const;

		FORCEINLINE void WriteProperty(const std::string& Name, const std::string& Value);

		FORCEINLINE void NewLine();

		FORCEINLINE size_t ScanForProperty(const std::string& Property) const;

		FORCEINLINE const std::string& GetPropertyRawString(const std::string& Property) const;

		template<typename T>
		FORCEINLINE T Get(const std::string& Property) const;

		template<>
		FORCEINLINE float Get(const std::string& Property) const;
		template<>
		FORCEINLINE int Get(const std::string& Property) const;
		template<>
		FORCEINLINE double Get(const std::string& Property) const;
		template<>
		FORCEINLINE long double Get(const std::string& Property) const;
		template<>
		FORCEINLINE unsigned int Get(const std::string& Property) const;
		template<>
		FORCEINLINE std::string Get(const std::string& Property) const;
		template<>
		FORCEINLINE bool Get(const std::string& Property) const;

		template<typename T>
		FORCEINLINE T Get(const std::string& Property, const T& Default) const;

		template<>
		FORCEINLINE float Get(const std::string& Property, const float& Default) const;
		template<>
		FORCEINLINE int Get(const std::string& Property, const int& Default) const;
		template<>
		FORCEINLINE double Get(const std::string& Property, const double& Default) const;
		template<>
		FORCEINLINE long double Get(const std::string& Property, const long double& Default) const;
		template<>
		FORCEINLINE unsigned int Get(const std::string& Property, const unsigned int& Default) const;
		template<>
		FORCEINLINE std::string Get(const std::string& Property, const std::string& Default) const;
		template<>
		FORCEINLINE bool Get(const std::string& Property, const bool& Default) const;

	};

}

#include "Aesset.inl"