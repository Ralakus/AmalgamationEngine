#pragma once

#include "File.hpp"
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

		static std::string ReadError() { return "Aesset_Read_Error"; }

		FORCEINLINE Aesset()  {}
		FORCEINLINE Aesset(const std::string& Data, bool IsFile = true, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app) {
			if (IsFile) {
				LoadFile(Data, Mode);
			}
			else {
				m_Content = Data;
			}
		}
		~Aesset() {}

		FORCEINLINE void LoadFile(const std::string& Name, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app) {
			m_Content = m_File.LoadAndGetContents(Name, Mode);
		}

		FORCEINLINE void LoadDataString(const std::string& Data) {
			m_Content = Data;
		}

		FORCEINLINE void Unload() {
			m_File.Close();
			m_Content.clear();
		}

		FORCEINLINE const std::string& GetData() const {
			return m_Content;
		}

		FORCEINLINE void WriteProperty(const std::string& Name, const std::string& Value) {
			m_File.Write("<" + Name + "/" + Value + ">");
		}

		FORCEINLINE size_t ScanForProperty(const std::string& Property) const {
			m_Buffer.clear();
			bool BufferDone = false;
			bool Buffering = false;
			//bool OnOpeningStatement = false;
			//bool OnClosingStatement = false;
			for (size_t i = 0; i < m_Content.size(); i++) {
				if (BufferDone) {
					m_Buffer.clear();
					BufferDone = false;
				}
				if (m_Content[i] == '<') {
					Buffering = true;
					i++;
				}
				if (Buffering) {
					m_Buffer += m_Content[i];
				}
				if (m_Content[i] == '/') {
					Buffering = false;
					BufferDone = true;
				}
				if (m_Buffer == Property) {
					return i + 2;
				}
			}
			printf("Could not find property %s\n", Property.c_str());
			return -1;
		}

		FORCEINLINE const std::string& GetPropertyRawString(const std::string& Property) const {
			size_t PropertyIndex = ScanForProperty(Property);
			if (PropertyIndex == static_cast<size_t>(-1)) {
				m_Buffer = ReadError();
				return m_Buffer;
			}
			m_Buffer.clear();
			for (size_t i = PropertyIndex; i < m_Content.size(); i++) {
				if (m_Content[i] == '>') {
					return m_Buffer;
				}
				m_Buffer += m_Content[i];
			}
			m_Buffer = ReadError();
			return m_Buffer;
		}

		template<typename T>
		FORCEINLINE T Get(const std::string& Property) const {
			static_assert(false, "Invalid property type");
		}

		template<>
		FORCEINLINE float Get(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			float Value = 0.f;
			try {
				if (str != "" && str != ReadError()) {
					Value = std::stof(str);
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a float!\n").c_str());
				return 0;
			}
			return Value;
		}

		template<>
		FORCEINLINE int Get(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			int Value = 0;
			try {
				if (str != "" && str != ReadError()) {
					Value = std::stoi(str);
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an int!\n").c_str());
				return 0;
			}
			return Value;
		}

		template<>
		FORCEINLINE double Get(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			double Value = 0.0;
			try {
				if (str != "" && str != ReadError()) {
					Value = std::stod(str);
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a double!\n").c_str());
				return 0;
			}
			return Value;
		}

		template<>
		FORCEINLINE long double Get(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			double Value = 0.0;
			try {
				if (str != "" && str != ReadError()) {
					Value = std::stold(str);
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a long double!\n").c_str());
				return 0;
			}
			return Value;
		}

		template<>
		FORCEINLINE unsigned int Get(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			unsigned int Value = 0;
			try {
				if (str != "" && str != ReadError()) {
					Value = std::stol(str);
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an unsigned int!\n").c_str());
				return 0;
			}
			return Value;
		}

		template<>
		FORCEINLINE std::string Get(const std::string& Property) const {
			std::string Value;
			try {
				Value = GetPropertyRawString(Property);
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
				return "";
			}
			return Value;
		}

		template<>
		FORCEINLINE bool Get(const std::string& Property) const {
			std::string Value;
			try {
				Value = GetPropertyRawString(Property);
				if (Value == "True" || Value == "true" || Value == "TRUE") {
					return true;
				}
				else if (Value == "False" || Value == "false" || Value == "FALSE") {
					return false;
				}
				else {
					throw Error("Property not bool!");
				}
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a bool!\n").c_str());
				return false;
			}
			return false;
		}

	};

}