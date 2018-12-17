
namespace Amalgamation {

	FORCEINLINE File::File() {}

	FORCEINLINE File::File(const std::string & FilePath, unsigned int Mode) { LoadFile(FilePath, Mode); }

	FORCEINLINE File::~File() {}

	FORCEINLINE void File::LoadFile(const std::string & FileName, unsigned int Mode) {
		m_File = FileName;
		m_Stream.open(FileName, static_cast<std::ios_base::openmode>(Mode));
		m_LoadedContent = std::string(
			std::istreambuf_iterator<char>(m_Stream.rdbuf()),
			std::istreambuf_iterator<char>()
		);
	}

	FORCEINLINE const std::string & File::GetContent() const {
		return m_LoadedContent;
	}

	FORCEINLINE const std::string & File::LoadAndGetContents(const std::string & FileName, unsigned int Mode) {
		LoadFile(FileName, Mode);
		return m_LoadedContent;
	}

	FORCEINLINE void File::Write(const std::string & Data) {
		if (m_Stream.is_open()) {
			m_Stream << Data;
		}
	}

	FORCEINLINE void File::Close() {
		m_Stream.close();
	}

}