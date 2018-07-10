#pragma once 

#include <Core/Utilities/File.hpp>
#include <string>
#include <unordered_map>

namespace Amalgamation {

	/*

	Goal for new Aesset reader is to have an API like

	Aesset Config("File.txt");
	float  FOV = Config["UserSettings"]["Graphics"]["FOV"].as<float>(90.f); //The 90.f is there incase the property doesn't exist
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

	private:

		File m_File;
		bool m_IsParsed = false;
		std::unordered_map<std::string, Aesset2> m_PropertMap;

		mutable std::string m_Buffer;


	public:


		Aesset2 operator[](const std::string& Property);


	};


}

#ifndef AE_NO_IMPL
	#include "Aesset2.inl"
#endif