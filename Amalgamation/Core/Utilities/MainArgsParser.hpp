#pragma once

#include "../Platform/Typedef.hpp"
#include "../Types/Singleton.hpp"
#include <string>
#include <vector>

namespace Amalgamation{

    class MainArgsParser {

    public:

        MainArgsParser()  {}
        ~MainArgsParser() {}

		SINGLETON_INSTANCE(MainArgsParser);

        std::vector<std::string> ParseMainArgs(int Count, char* Args[]){
            std::vector<std::string> Strings;
            for(int i = 0; i < Count; i++){
                Strings.emplace_back(Args[i]);
            }
            return Strings;
        }

    };

}
