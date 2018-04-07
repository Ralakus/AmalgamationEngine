#pragma once

#include "File.hpp"
#include <Core/Types/Singleton.hpp>
#include <string>

namespace Amalgamation {

	class AessetReader : public Singleton<AessetReader> {

		std::string m_LoadedFile;

		std::string m_LoadedFilePath;

		mutable std::string m_Buffer;

	public:

		const std::string ReadError = "AESSET_READ_ERROR";

		bool LoadAeseet(const std::string& Location) {

			m_LoadedFilePath = Location;
			m_LoadedFile = File::ReadFile(Location);
			m_Buffer.clear();
			if (m_LoadedFile == "") {
				return false;
			}
			else {
				return true;
			}

		}

		bool LoadAessetFromStr(const std::string& Aesset) {
			m_LoadedFile = Aesset;
			m_Buffer.clear();
			if (m_LoadedFile == "") {
				return false;
			}
			else {
				return true;
			}
		}

		int ScanForProperty(const std::string& Property) const {

			m_Buffer.clear();

			bool BufferDone = false;
			bool Buffering = false;
			//bool OnOpeningStatement = false;
			//bool OnClosingStatement = false;

			for (int i = 0; i < m_LoadedFile.size(); i++) {
				if (BufferDone) {
					m_Buffer.clear();
					BufferDone = false;
				}
				if (m_LoadedFile[i] == '<') {
					Buffering = true;
					i++;
				}
				if (Buffering) {
					m_Buffer += m_LoadedFile[i];
				}
				if (m_LoadedFile[i] == '/') {
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

		const std::string& GetPropertyRawString(const std::string& Property) const {

			int PropertyIndex = ScanForProperty(Property);
			if (PropertyIndex == -1) {
				return ReadError;
			}
			m_Buffer.clear();

			for (int i = PropertyIndex; i < m_LoadedFile.size(); i++) {
				if (m_LoadedFile[i] == '>') {
					return m_Buffer;
				}
				m_Buffer += m_LoadedFile[i];
			}
			return ReadError;

		}

		void UnloadAesset() {
			m_LoadedFilePath.clear();
			m_LoadedFile.clear();
			m_Buffer.clear();
		}

		const std::string& GetLoadedFile() const { return m_LoadedFilePath; }

		template<typename T>
		T GetProperty(const std::string& Property) const {
			static_assert(false, "Invalid property type");
		}

		template<>
		float GetProperty(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			float Value = 0.f;
			try {
				if (str != "" && str != ReadError) {
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
		int GetProperty(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			int Value = 0;
			try {
				if (str != "" && str != ReadError) {
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
		double GetProperty(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			double Value = 0.0;
			try {
				if (str != "" && str != ReadError) {
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
		long double GetProperty(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			double Value = 0.0;
			try {
				if (str != "" && str != ReadError) {
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
		unsigned int GetProperty(const std::string& Property) const {
			std::string str = GetPropertyRawString(Property);
			unsigned int Value = 0;
			try {
				if (str != "" && str != ReadError) {
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
		std::string GetProperty(const std::string& Property) const {
			std::string Value = "";
			try {
				Value = GetPropertyRawString(Property);
			}
			catch (...) {
				printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
				return 0;
			}
			return Value;
		}

	};
}