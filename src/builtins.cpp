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
    if(args[0] == "cd"){
    const char* target = nullptr;
    if(args.size() == 1){
        target = getenv("HOME");
    } 
    else if(args.size() == 2){
        target = args[1].c_str();
    } 
    else {
        std::cerr <<"mysh: cd: Too many arguments!\n";
        return true;
    }
    if(target == nullptr){
        std::cerr <<"mysh: cd: HOME not set.\n";
        return true;
    }
    if(chdir(target) == -1){
        std::perror("mysh: cd");
    }
    return true;
}
}