#pragma once 

#include <Core/Platform/Platform.hpp>
#include <Core/Detail/StringFunctions.hpp>

#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>

#define AE_INVALID_AESSET "INVALID_AESSET"

namespace Amalgamation {

	/*

	Goal for new Aesset reader is to have an API like

	Aesset Config("File.txt");
	float  FOV = Config["UserSettings"]["Graphics"]["FOV"].As<float>(90.f); //The 90.f is there incase the property doesn't exist
	//The class will automatically write the property and it's default value if it doesn't exist

	//Or you could do it manually
	Config["UserSettings"]["Graphics"].Write<float>("FOV", 90.f);

	//You will also be able to edit values
	Config["UserSettings"]["Graphics"]["FOV"].Set<float>(100.f);

	*/

	class Aesset2 {

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

		enum class Type : unsigned char {
			Aesset = 0, Other = 1
		};

	private:

		bool m_IsParsed = false;
		std::unordered_map<std::string, std::unique_ptr<Aesset2>> m_PropertyMap;
		std::string m_Content;
		Type m_Type;

		mutable std::string m_Buffer;


	public:

		void LoadFile(const std::string& Name);
		void LoadStr(const std::string& Data);
		void Unload() { m_PropertyMap.clear(); m_Content.clear(); }

		Aesset2& operator[](const std::string& Property);

		int ParseAesset();

		static std::vector<char> ReadFile(const std::string& Filename);
		static Aesset2& GetInvalidAesset();

		const std::string& GetRaw() const { return m_Content; }

		const std::string& AsString(const std::string& Default) const { return m_Content == AE_INVALID_AESSET ? Default : m_Content; }
		const std::string& AsString() const { return m_Content; }

		template<class T>
		T As() {
			T R;
			if (!m_Content.empty() && m_Content != AE_INVALID_AESSET) {
				try {
					R = Detail::FromString<T>(m_Content);
				}
				catch (std::exception& e) {

				}
			}
			return R;
		}

		template<class T>
		T As(T Default) {
			T R = Default;
			if (!m_Content.empty() && m_Content != AE_INVALID_AESSET) {
				try {
					R = Detail::FromString<T>(m_Content);
				}
				catch (std::exception& e) {

				}
			}
			return R;
		}

	};


}

#ifndef AE_NO_IMPL
	#include "Aesset2.inl"
#endif