#pragma once

#include <fstream>

namespace Amalgamation {

	class File {

	public:

		static std::string ReadFile(const std::string& filepath) {
			std::ifstream ifs((filepath).c_str());
			std::string content(
				std::istreambuf_iterator<char>(ifs.rdbuf()),
				std::istreambuf_iterator<char>()
			);
			return content;
		}

		static std::string ReadFile(const char* filepath) {
			std::ifstream ifs(filepath);
			std::string content(
				std::istreambuf_iterator<char>(ifs.rdbuf()),
				std::istreambuf_iterator<char>()
			);
			return content;
		}


		static void WriteToFile(const std::string& Destination, const std::string& Data) {

		}

	};

}