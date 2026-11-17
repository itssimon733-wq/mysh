#include "tokenizer.hpp"
#include <cctype> /*Provides std::isspace()*/
#include <iostream> /*Provides std::cerr*/

bool tokenizeInput(std::string& entry, std::vector<std::string>& args){
    std::string current;
    bool inDoubleQuotes = false;
    bool inSingleQuotes = false;
    bool escapeNext = false;
    bool tokenStarted = false;
    args.clear();

    for(char c : entry){
        if(inSingleQuotes){
            if(c == '\''){
                inSingleQuotes = false;
            } else {
                current += c;
            }
            tokenStarted = true;
        }
        /*Merges the character after the slash to the text this way a quotation mark after the slash is displayed on the console*/
        else if(escapeNext){
            current += c;
            escapeNext = false;
            tokenStarted = true;
        }
        else if(c == '\\'){
            escapeNext = true;
            tokenStarted = true;
        }
        else if(c == '\'' && !inDoubleQuotes){
            inSingleQuotes = true;
            tokenStarted = true;
        }
        /*Opening or closing quotation marks*/
        else if(c == '"'){
            inDoubleQuotes = !inDoubleQuotes;
            tokenStarted = true;
        }
        /*Space outside quotation marks*/
        else if(std::isspace(static_cast<unsigned char>(c)) && !inDoubleQuotes){
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
        /*Detect a missing match slash*/
    if(escapeNext){
        std::cerr << "mysh: Unmatched escape character \n";
        return false;
    }
        /*Detect a missing match quatation mark*/
    if(inDoubleQuotes){
        std::cerr<< "mysh: Unmatched double quote\n";
        return false;
    }
        /*Detect a missing quotation mark*/
    if(inSingleQuotes || inDoubleQuotes){
        std::cerr << "mysh: unmatched quote\n";
        return false;
    }
    /*Save last argument*/
    if(tokenStarted){
        args.push_back(current);
    }
    return true;
}