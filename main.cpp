#include <iostream>
#include <string>
#include <vector>
#include <sstream>
void tokenize(){

}
void prompt(){
    std::string entry;
    while(std::cout<<"mysh> " && std::getline(std::cin, entry)){
        if(entry == "exit"){break;}
        std::istringstream ss(entry);//splits the input in the entry variable by spaces
        std::string word;
        std::vector<std::string> args;// a dynamic array where each argument of the entry variable is stored
        while(ss >> word){// the '>>' operator acts like a vaccum moving one argument at a time to the 'word' variable
            args.push_back(word);//adds each argument moved to the word variable in args
        }
        if(args.empty()){//checks if the user has entered any text
            continue;
        }
        std::cout<<"-> Parsed command: "<<args[0]<<"\n";
        for(size_t i = 1; i < args.size(); ++i){
            std::cout<<"-> Argument "<<i<<": "<<args[i]<<"\n";
        }

    }
    if(std::cin.eof()){std::cout<<"\n";}
}

int main(){
    prompt();
}