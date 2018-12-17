#pragma once

#include "../Platform/Platform.hpp"

#include <fstream>

namespace Amalgamation {

	class File {

		friend class Aesset;

		std::string m_File;
		std::string m_LoadedContent;
		std::fstream m_Stream;

	public:

		FORCEINLINE File();
		FORCEINLINE File(const std::string& FilePath, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);
		FORCEINLINE ~File();

		FORCEINLINE void LoadFile(const std::string& FileName, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);

		FORCEINLINE const std::string& GetContent() const;

		FORCEINLINE const std::string& LoadAndGetContents(const std::string& FileName, unsigned int Mode = std::ios::in | std::ios::out | std::ios::app);

		FORCEINLINE void Write(const std::string& Data);

		FORCEINLINE void Close();

	};

}

#if !defined(AE_NO_IMPL)
	#include "File.inl"
#endif
