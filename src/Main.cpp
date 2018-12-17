#include <iostream>
#include <cxxopts.hpp>

namespace Amalgamation {
    constexpr auto version = "0.1.0";
}

int main(int argc, char* argv[]) {

    cxxopts::Options options("Amalgamation", "This is a project made using the Amalgamation Engine");

    options.add_options()
        ("v,version", "Displays version")
        ("h,help", "Prints help")
    ;

    options.help({""});

    try {
        auto cxxresult = options.parse(argc, argv);

        if(cxxresult.count("help")) {
            std::cout << options.help() << std::endl;
            return EXIT_SUCCESS;
        }

        if(cxxresult.count("version")) {
            std::cout << "Amalgamation version: " << Amalgamation::version << std::endl;
            return EXIT_SUCCESS;
        }

    } catch (cxxopts::OptionException& e) {

        std::cout << e.what() << std::endl;

    }

    return EXIT_SUCCESS;

}
