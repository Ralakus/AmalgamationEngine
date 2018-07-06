#include "Aesset.hpp"


namespace Amalgamation {

	FORCEINLINE std::string Aesset::ReadError() { return "Aesset_Read_Error"; }

	FORCEINLINE Aesset::Aesset() {}

	FORCEINLINE Aesset::Aesset(const std::string & Data, bool IsFile, bool ParseData, unsigned int Mode) {
		if (IsFile) {
			LoadFile(Data, ParseData, Mode);
		}
		else {
			m_Content = Data;
		}
	}

	FORCEINLINE Aesset::~Aesset() {}

	FORCEINLINE void Aesset::LoadFile(const std::string & Name, bool ParseData, unsigned int Mode) {
		m_Content = m_File.LoadAndGetContents(Name, Mode);
		if (ParseData) { ParseAesset(); }
	}

	FORCEINLINE void Aesset::LoadDataString(const std::string & Data, bool ParseData) {
		m_Content = Data;
		if (ParseData) { ParseAesset(); }
	}

	FORCEINLINE void Aesset::Unload() {
		m_File.Close();
		m_Content.clear();
		m_PropertyMap.clear();
	}

	FORCEINLINE const std::string & Aesset::GetData() const {
		return m_Content;
	}

	FORCEINLINE void Aesset::WriteProperty(const std::string & Name, const std::string & Value) {
		m_File.Write("<" + Name + "/" + Value + ">");
	}

	FORCEINLINE void Aesset::WriteProperty(const Property & Prop) {
		m_File.Write("<" + Prop.Name + "/" + Prop.Value + ">");
	}

	FORCEINLINE void Aesset::ParseAesset() {
		m_PropertyMap.clear();
		m_Buffer.clear();
		enum class State {
			Name, Value, Scanning
		} ParseState = State::Scanning;
		size_t PassedOpenings = 0;
		Property Buffer = { "", "" };
		size_t AessetSize = m_Content.size();
		for (size_t i = 0; i < AessetSize; i++) {
			switch (ParseState) {
				case State::Name: {
				
					if (m_Content[i] == '/') {
						if (m_Buffer == "") {
							//Log::Error("Property at iterator " + std::to_string(i) + " has no name!");
						}
						else {
							Buffer.Name = m_Buffer;
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
					}
					else if(m_Content[i] == '>'){
						if (PassedOpenings == 0) {
							if(m_Buffer == ""){
								//Log::Error("Property \"" + Buffer.Name + " has no value!");
							}
							else {
								Buffer.Value = m_Buffer;
								m_Buffer.clear();
								m_PropertyMap[Buffer.Name] = Buffer.Value;
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
		m_Content.clear();
	}

	FORCEINLINE void Aesset::NewLineInFile() {
		m_File.Write("\n");
	}

	FORCEINLINE bool Aesset::HasProperty(const std::string & Name) const{
		if (m_PropertyMap.count(Name) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE Aesset::Property Aesset::GetProperty(const std::string Name) const {
		if (HasProperty(Name)) {
			return { Name, m_PropertyMap.at(Name) };
		}
		else {
			return { ReadError(), ReadError() };
		}
	}

	template<typename T>
	FORCEINLINE T Aesset::Get(const std::string & Property) const {
		static_assert(false, "Invalid property type");
	}

	template<>
	FORCEINLINE float Aesset::Get(const std::string & Property) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		float Value = 0.f;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stof(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a float!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into float!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE int Aesset::Get(const std::string & Property) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stoi(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an int!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into int!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE double Aesset::Get(const std::string & Property) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stod(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a double!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into double!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE long double Aesset::Get(const std::string & Property) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stold(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a long double!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into long double!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE unsigned int Aesset::Get(const std::string & Property) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		unsigned int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stol(str);
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an unsigned int!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into unsigned int!");
			return 0;
		}
		return Value;
	}

	template<>
	FORCEINLINE std::string Aesset::Get(const std::string & Property) const {
		std::string Value;
		try {
			if (m_PropertyMap.count(Property) > 0) {
				Value = m_PropertyMap.at(Property);
			}
			else {
				Value = ReadError();
				throw std::runtime_error("Property not found!");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into string!");
			return "";
		}
		return Value;
	}

	template<>
	FORCEINLINE bool Aesset::Get(const std::string & Property) const {
		std::string Value;
		try {
			if (m_PropertyMap.count(Property) > 0) {
				Value = m_PropertyMap.at(Property);
			}
			else {
				Value = ReadError();
				throw std::runtime_error("Property not found!");
			}
			if (Value == "True" || Value == "true" || Value == "TRUE") {
				return true;
			}
			else if (Value == "False" || Value == "false" || Value == "FALSE") {
				return false;
			}
			else {
				throw std::runtime_error("Property not bool!");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a bool!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into bool!");
			return false;
		}
		return false;
	}

	template<>
	FORCEINLINE Aesset::Property Aesset::Get(const std::string& Property) const {
		if (HasProperty(Property)) {
			return GetProperty(Property);
		}
		else {
			//Log::Error(Property + " property not in aesset!");
			return { ReadError(), ReadError() };
		}
	}

	template<typename T>
	FORCEINLINE T Aesset::Get(const std::string & Property, const T& Default) const {
		static_assert(false, "Invalid property type");
	}

	template<>
	FORCEINLINE float Aesset::Get(const std::string & Property, const float& Default) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		float Value = 0.f;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stof(str);
			}
			else {
				throw std::runtime_error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a float!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into float!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE int Aesset::Get(const std::string & Property, const int& Default) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		int Value = Default;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stoi(str);
			}
			else {
				throw std::runtime_error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an int!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into int!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE double Aesset::Get(const std::string & Property, const double& Default) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stod(str);
			}
			else {
				throw std::runtime_error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a double!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into double!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE long double Aesset::Get(const std::string & Property, const long double& Default) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		double Value = 0.0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stold(str);
			}
			else {
				throw std::runtime_error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a long double!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into long double!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE unsigned int Aesset::Get(const std::string & Property, const unsigned int& Default) const {
		std::string str;
		if (m_PropertyMap.count(Property) > 0) {
			str = m_PropertyMap.at(Property);
		}
		else {
			str = ReadError();
		}
		unsigned int Value = 0;
		try {
			if (str != "" && str != ReadError()) {
				Value = std::stol(str);
			}
			else {
				throw std::runtime_error("ReadError");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into an unsigned int!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into unsigned int!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE std::string Aesset::Get(const std::string & Property, const std::string& Default) const {
		std::string Value;
		try {
			if (m_PropertyMap.count(Property) > 0) {
				Value = m_PropertyMap.at(Property);
			}
			else {
				Value = ReadError();
				throw std::runtime_error("Property not found!");
			}
		}
		catch (...) {
			printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			return Default;
		}
		if (Value == ReadError()) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a string!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into string!\nLoading default value of \"" + Default + "\" in place");
			return Default;
		}
		return Value;
	}

	template<>
	FORCEINLINE bool Aesset::Get(const std::string & Property, const bool& Default) const {
		std::string Value;
		try {
			if (m_PropertyMap.count(Property) > 0) {
				Value = m_PropertyMap.at(Property);
			}
			else {
				Value = ReadError();
				throw std::runtime_error("Property not found!");
			}
			if (Value == "True" || Value == "true" || Value == "TRUE") {
				return true;
			}
			else if (Value == "False" || Value == "false" || Value == "FALSE") {
				return false;
			}
			else {
				throw std::runtime_error("Property not bool!");
			}
		}
		catch (...) {
			//printf("%s", ("[LOG_ERROR]: Failed to parse " + Property + " into a bool!\n").c_str());
			//Log::Error("Failed to parse " + Property + " into bool!\nLoading default value of \"" + std::to_string(Default) + "\" in place");
			return Default;
		}
		return Default;
	}

	template<>
	FORCEINLINE Aesset::Property Aesset::Get(const std::string& Prop, const Property& Default) const {
		if (HasProperty(Prop)) {
			return GetProperty(Prop);
		}
		else {
			//Log::Error(Prop + " property not in aesset!\nLoading default value of \"" + Default.Name + '/' + Default.Value  + "\" in place");
			return Default;
		}
	}

}