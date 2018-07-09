#pragma once 

#include <Core/Utilities/File.hpp>
#include <string>
#include <unordered_map>

namespace Amalgamation {


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