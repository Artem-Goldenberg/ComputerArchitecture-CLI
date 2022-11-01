#include "preprocessor.h"

Preprocessor::Preprocessor() {

}

Preprocessor::~Preprocessor() {

}

Result Preprocessor::substitute(const std::string &in, const Environment &env) {
    size_t inputLenght = in.length();
    std::string result;
    result.reserve(inputLenght);
    
    bool isSingleQuoted = false, isDoubleQuoted = false;
    
    for (int i = 0; i < inputLenght;) {
        bool notQuoted = !isSingleQuoted && !isDoubleQuoted;
        
        if (notQuoted && in[i] == this->varIndicator) {
            // remember start of the name (skip $)
            int k = ++i;
            // find end of the name
            while (i < inputLenght && this->varTerminators.find(in[i]) == std::string::npos) i++;
            
            auto buffer = in.substr(k, i - k);
            if (env.findVar(buffer)) result += env.getVar(buffer);
            else return Result(Error, "Failed to find the variable: " + buffer);
        } else {
            if (in[i] == '\'') isSingleQuoted = !isSingleQuoted;
            if (in[i] == '\"') isDoubleQuoted = !isDoubleQuoted;
            result += in[i];
            i++;
        }
    }
    
    if (isSingleQuoted || isDoubleQuoted) {
        return Result(Error, "Quotes are not balanced");
    }
    
    return Result(Ok, result);
}

