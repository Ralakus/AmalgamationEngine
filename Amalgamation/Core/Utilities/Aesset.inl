

namespace Amalgamation {

	FORCEINLINE std::string Aesset::ReadError() { return "Aesset_Read_Error"; }

	FORCEINLINE Aesset::Aesset() {}

	FORCEINLINE Aesset::Aesset(const std::string & Data, bool IsFile, unsigned int Mode) {
		if (IsFile) {
			LoadFile(Data, Mode);
		}
		else {
			m_Content = Data;
		}
	}

	FORCEINLINE Aesset::~Aesset() {}

	FORCEINLINE void Aesset::LoadFile(const std::string & Name, unsigned int Mode) {
		m_Content = m_File.LoadAndGetContents(Name, Mode);
	}

	FORCEINLINE void Aesset::LoadDataString(const std::string & Data) {
		m_Content = Data;
	}

	FORCEINLINE void Aesset::Unload() {
		m_File.Close();
		m_Content.clear();
	}

	FORCEINLINE const std::string & Aesset::GetData() const {
		return m_Content;
	}

	FORCEINLINE void Aesset::WriteProperty(const std::string & Name, const std::string & Value) {
		m_File.Write("<" + Name + "/" + Value + ">");
	}

	FORCEINLINE void Aesset::NewLine() {
		m_File.Write("\n");
	}

	FORCEINLINE size_t Aesset::ScanForProperty(const std::string & Property) const {
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
		//printf("Could not find property %s\n", Property.c_str());
		Log::Error("Coud not find property " + Property);
		return -1;
	}

	FORCEINLINE const std::string & Aesset::GetPropertyRawString(const std::string & Property) const {
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
	FORCEINLINE T Aesset::Get(const std::string & Property) const {
		static_assert(false, "Invalid property type");
	}

	template<>
	FORCEINLINE float Aesset::Get(const std::string & Property) const {
		std::string str = GetPropertyRawString(Property);
		float Value = 0.f;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stof(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a float!\n").c_str());
			Log::Error("Failed to parse " + Property + " into float!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE int Aesset::Get(const std::string & Property) const {
		std::string str = GetPropertyRawString(Property);
		int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stoi(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an int!\n").c_str());
			Log::Error("Failed to parse " + Property + " into int!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE double Aesset::Get(const std::string & Property) const {
		std::string str = GetPropertyRawString(Property);
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stod(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a double!\n").c_str());
			Log::Error("Failed to parse " + Property + " into double!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE long double Aesset::Get(const std::string & Property) const {
		std::string str = GetPropertyRawString(Property);
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stold(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a long double!\n").c_str());
			Log::Error("Failed to parse " + Property + " into long double!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE unsigned int Aesset::Get(const std::string & Property) const {
		std::string str = GetPropertyRawString(Property);
		unsigned int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stol(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an unsigned int!\n").c_str());
			Log::Error("Failed to parse " + Property + " into unsigned int!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE std::string Aesset::Get(const std::string & Property) const {
		std::string Value;
		try {
			Value = GetPropertyRawString(Property);
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			Log::Error("Failed to parse " + Property + " into string!");
			return "";
		}
		return Value;
	}

	template<>
	FORCEINLINE bool Aesset::Get(const std::string & Property) const {
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
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a bool!\n").c_str());
			Log::Error("Failed to parse " + Property + " into bool!");
			return false;
		}
		return false;
	}

	template<typename T>
	FORCEINLINE T Aesset::Get(const std::string & Property, const T& Default) const {
		static_assert(false, "Invalid property type");
	}

	template<>
	FORCEINLINE float Aesset::Get(const std::string & Property, const float& Default) const {
		std::string str = GetPropertyRawString(Property);
		float Value = 0.f;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stof(str);
			}
			else {
				throw Error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a float!\n").c_str());
			Log::Error("Failed to parse " + Property + " into float!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE int Aesset::Get(const std::string & Property, const int& Default) const {
		std::string str = GetPropertyRawString(Property);
		int Value = Default;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stoi(str);
			}
			else {
				throw Error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an int!\n").c_str());
			Log::Error("Failed to parse " + Property + " into int!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE double Aesset::Get(const std::string & Property, const double& Default) const {
		std::string str = GetPropertyRawString(Property);
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stod(str);
			}
			else {
				throw Error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a double!\n").c_str());
			Log::Error("Failed to parse " + Property + " into double!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE long double Aesset::Get(const std::string & Property, const long double& Default) const {
		std::string str = GetPropertyRawString(Property);
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stold(str);
			}
			else {
				throw Error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a long double!\n").c_str());
			Log::Error("Failed to parse " + Property + " into long double!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE unsigned int Aesset::Get(const std::string & Property, const unsigned int& Default) const {
		std::string str = GetPropertyRawString(Property);
		unsigned int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stol(str);
			}
			else {
				throw Error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an unsigned int!\n").c_str());
			Log::Error("Failed to parse " + Property + " into unsigned int!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE std::string Aesset::Get(const std::string & Property, const std::string& Default) const {
		std::string Value;
		try {
			Value = GetPropertyRawString(Property);
		}
		catch (...) {
			printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			return Default;
		}
		if (Value == ReadError()) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			Log::Error("Failed to parse " + Property + " into string!\nLoading default value of \"" + Default + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE bool Aesset::Get(const std::string & Property, const bool& Default) const {
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
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a bool!\n").c_str());
			Log::Error("Failed to parse " + Property + " into bool!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Default;
	}

}