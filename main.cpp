#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>/*Required for fork() and execvp()*/
#include <sys/wait.h>/*Required for waitpid()*/
#include <cstdlib>/*Required for chdir()*/
#include <cctype>
bool tokenizeInput(std::string& entry, std::vector<std::string>& args){
    std::string current;
    bool inQuotes = false;
    bool tokenStarted = false;
    for(char c : entry){
        /*Opening or closing quotation marks*/
        if(c == '"'){
            inQuotes = !inQuotes;
            tokenStarted = true;
        }
        /*Space outside quotation marks*/
        else if(std::isspace(static_cast<unsigned char>(c)) && !inQuotes){
            if(tokenStarted){
                args.push_back(current);
                current.clear();
                tokenStarted = false;
            }
        }
        /*Ordinary character*/
        else{
            current += c;
            tokenStarted = true;
        }
    }
        /*Detect a missing match quatation mark*/
    if(inQuotes){
        std::cerr<< "mysh: Unmatched double quote\n";
        return false;
    }
    /*Save last argument*/
    if(tokenStarted){
        args.push_back(current);
    }
    return true;
}
void tokenizeAndExecute(std::string entry){
    /*====================Tokenization====================*/
    std::vector<std::string> args;
    if(!tokenizeInput(entry, args)){
        return;
    }
    if(args.empty()){//checks if the user has entered any text
        return;
    }
    /*====================Execution and error handling====================*/
    if(args[0] == "exit"){
        std::exit(0);
    }
    if(args[0] == "cd"){
        const char* target = nullptr;
        if(args.size() == 1){
            target = getenv("HOME");
        }else if(args.size() == 2){
            target = args[1].c_str();
        }else{
            std::cerr <<"mysh: cd: Too many arguments!\n";
        }
        if(target == nullptr){
            std::cerr <<"mysh: cd: HOME not set.\n";
        }
        if(chdir(target) == -1){
            std::perror("mysh: cd");
        }
        return;
    }
    std::vector<char*> c_args;
    for(const auto& arg : args){
        c_args.push_back(const_cast<char*>(arg.c_str()));
    }
    c_args.push_back(nullptr);
    /*Cloning the process*/
    pid_t pid = fork();

    if(pid < 0){
        /*Fork failed*/
        std::perror("mysh: fork");
        return;
    }else if(pid == 0){
        /*Forking was successful and a clone takes over the operations*/
        if(execvp(c_args[0], c_args.data()) == -1){
            std::perror("mysh");
            _exit(1);
        }
    }
    else{
        int status;
        waitpid(pid, &status,0);
    }

    
    /*std::cout<<"-> Parsed command: "<<args[0]<<"\n";
    for(size_t i = 1; i < args.size(); ++i){
        std::cout<<"-> Argument "<<i<<": "<<args[i]<<"\n";*/
    
}
void prompt(){
    std::string entry;
    while(std::cout<<"mysh> " && std::getline(std::cin, entry)){
        tokenizeAndExecute(entry);
    }
    if(std::cin.eof()){std::cout<<"\n";}
}

int main(){
    prompt();
}