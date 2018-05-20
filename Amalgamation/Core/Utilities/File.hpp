#pragma once

#include <fstream>

namespace Amalgamation {

	class FileIO {

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

		static void WriteToFile(const std::string& NameAndLocation, const std::string& Data, std::ios_base::openmode Mode = std::ios::app) {
            static std::ofstream OutputFile;
            static std::string LastFile = "";
            static std::ios_base::openmode LastMode = std::ios::app;
            if(NameAndLocation == LastFile && Mode == LastMode){
                OutputFile << Data << '\n';
            }
            else{
                OutputFile.close();
                OutputFile.open(NameAndLocation, Mode);
            }
            LastFile = NameAndLocation;
            LastMode = Mode;
		}

	};

}
