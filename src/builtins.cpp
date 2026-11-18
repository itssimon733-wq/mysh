#include "builtins.hpp"
#include <iostream>  // std::cerr
#include <cstdlib>   // std::getenv(), std::exit()
#include <unistd.h>  // chdir()

bool handleBuiltin(const std::vector<std::string>& args){
    if (args.empty()) {
        return false;
    }

    if (args[0] == "exit") {
        std::exit(0);
    }
    return false;
}