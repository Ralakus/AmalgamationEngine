#pragma once

#include "File.hpp"

#include <unordered_map>
#include <string>

namespace Amalgamation {

	using AessetDataInfo = std::unordered_map<std::string, std::pair<size_t, size_t>>; //Property name, value header, value end
	using AessetPropertyDataInfo = std::pair<std::string, std::pair<size_t, size_t>>;  //Property name, value header, value end

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

	public:
		struct Property {
			std::string Name = "";
			std::string Value = "";
			enum class Type {
				String, Number, StringArray, NumberArray
			};
		};
	private:

		File m_File;
		std::string m_Content;
		std::unordered_map<std::string, std::string> m_PropertyMap;

		mutable std::string m_Buffer;

	public:

		static std::string ReadError();

		FORCEINLINE Aesset();
		FORCEINLINE Aesset(const std::string& Data, bool IsFile = true, bool ParseData = true, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);
		~Aesset();

		FORCEINLINE void LoadFile(const std::string& Name, bool ParseData = true, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);

		FORCEINLINE void LoadDataString(const std::string& Data, bool ParseData = true);

		FORCEINLINE void Unload();

		FORCEINLINE const std::string& GetData() const;

		FORCEINLINE void WriteProperty(const std::string& Name, const std::string& Value);
		FORCEINLINE void WriteProperty(const Property& Prop);

		FORCEINLINE void ParseAesset();

		FORCEINLINE void NewLineInFile();

		FORCEINLINE bool HasProperty(const std::string& Name) const;
		FORCEINLINE Property GetProperty(const std::string Name) const;

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
		template<>
		FORCEINLINE Property Get(const std::string& Property) const;

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
		template<>
		FORCEINLINE Property Get(const std::string& Prop, const Property& Default) const;

	};

}
#if !defined(AE_NO_IMPL)
	#include "Aesset.inl"
#endif