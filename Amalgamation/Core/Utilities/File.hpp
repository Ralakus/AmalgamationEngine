#pragma once

#include "../Platform/Typedef.hpp"
#include <fstream>

namespace Amalgamation {

	class File {

		friend class Aesset;

		std::string m_File;
		std::string m_LoadedContent;
		std::fstream m_Stream;

	public:

		FORCEINLINE File()  {}
		FORCEINLINE File(const std::string& FilePath, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app) { LoadFile(FilePath, Mode); }
		FORCEINLINE ~File() {}

		FORCEINLINE void LoadFile(const std::string& FileName, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app) {
			m_File = FileName;
			m_Stream.open(FileName, static_cast<std::ios_base::openmode>(Mode));
			m_LoadedContent = std::string(
				std::istreambuf_iterator<char>(m_Stream.rdbuf()),
				std::istreambuf_iterator<char>()
			);
		}

		FORCEINLINE const std::string& GetContent() const {
			return m_LoadedContent;
		}

		FORCEINLINE const std::string& LoadAndGetContents(const std::string& FileName, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app) {
			LoadFile(FileName, Mode);
			return m_LoadedContent;
		}

		FORCEINLINE void Write(const std::string& Data) {
			if (m_Stream.is_open()) {
				m_Stream << Data;
			}
		}

		FORCEINLINE void Close() {
			m_Stream.close();
		}

	};

}
