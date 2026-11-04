#include <iostream>
#include <string>
#include <vector>
void prompt(){
    std::string entry;
    while(std::cout<<"mysh> " && std::getline(std::cin, entry)){
        if(entry == "exit"){break;}
    }
    if(std::cin.eof()){std::cout<<"\n";}
}

int main(){
    prompt();
}