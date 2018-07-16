
namespace Amalgamation {

	Aesset2& Aesset2::operator[](const std::string & Property) {
		if (m_PropertyMap.count(Property) < 1) { return GetInvalidAesset(); }
		if (!m_PropertyMap[Property]->m_IsParsed) { m_PropertyMap[Property]->ParseAesset(); }
		return *m_PropertyMap[Property];
	}

	int Aesset2::ParseAesset() {
		m_PropertyMap.clear();
		m_Buffer.clear();
		enum class State {
			Name, Value, Scanning
		} ParseState = State::Scanning;
		size_t PassedOpenings = 0;
		
		std::string NameBuffer, ValueBuffer;
		Type TypeBuffer = Type::Other;

		size_t AessetSize = m_Content.size();
		for (size_t i = 0; i < AessetSize; i++) {
			switch (ParseState) {
			case State::Name: {

				if (m_Content[i] == '/') {
					if (m_Buffer == "") {
						//Log::Error("Property at iterator " + std::to_string(i) + " has no name!");
					}
					else {
						//Buffer.Name = m_Buffer;
						NameBuffer = m_Buffer;
						m_Buffer.clear();
						ParseState = State::Value;
					}
				}
				else if (m_Content[i] == '>') {
					//Log::Error("Property \"" + m_Buffer + "\" has no value statement!");
					ParseState = State::Scanning;
					m_Buffer.clear();
				}
				else {
					m_Buffer += m_Content[i];
				}


			} break;
			case State::Value: {


				if (m_Content[i] == '<') {
					m_Buffer += '<';
					PassedOpenings++;
					TypeBuffer = Type::Aesset;
				}
				else if (m_Content[i] == '>') {
					if (PassedOpenings == 0) {
						if (m_Buffer == "") {
							//Log::Error("Property \"" + Buffer.Name + " has no value!");
						}
						else {
							//Buffer.Value = m_Buffer;
							ValueBuffer = m_Buffer;
							m_Buffer.clear();
							m_PropertyMap[NameBuffer] = std::make_unique<Aesset2>();
							m_PropertyMap[NameBuffer]->m_Content = ValueBuffer;
							if (m_PropertyMap[NameBuffer]->m_Type == Type::Aesset) {
								m_PropertyMap[NameBuffer]->ParseAesset();
							}
							ParseState = State::Scanning;
						}
					}
					else {
						m_Buffer += '>';
						PassedOpenings--;
					}
				}
				else if (i == m_Content.length() - 1) {
					//Log::Error("Property \"" + Buffer.Name + "\" does not have a closing >!");
					ParseState = State::Scanning;
				}
				else {
					m_Buffer += m_Content[i];
				}


			} break;
			case State::Scanning: {

				if (m_Content[i] == '<') {
					ParseState = State::Name;
				}

			} break;
			default: {} break;
			}
		}
		//m_Content.clear();
		m_IsParsed = true;
		return 0;
	}


	std::vector<char> Aesset2::ReadFile(const std::string& Filename) {
		std::ifstream file(Filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	inline void Aesset2::LoadFile(const std::string& Name){
		auto Data = ReadFile(Name);
		m_Content = std::string(Data.begin(), Data.end());
		ParseAesset();
	}

	inline void Aesset2::LoadStr(const std::string& Data) {
		m_Content = Data;
		ParseAesset();
	}


	Aesset2& Aesset2::GetInvalidAesset()
	{
		static Aesset2 m_Invalid;
		m_Invalid.m_Content = AE_INVALID_AESSET;
		return m_Invalid;
	}
}