#include <string>
#include <unordered_map>
#include <string_view>

#pragma once

/**
 Abstraction of a shell environment
 
 Stores variables in the internal hashtable
 Can be accessed by shell entities for reading and writing
 */
class Environment {
    public:
        ///Initialize `Environment` with no stored variables
        Environment();
        ~Environment();

        /**
         Determine wheter the environment has a variable with name `str` or not
         
         - Parameter str: name of the variable to check
         - Returns: `true` if variable is found, `false` otherwise
         */
        bool findVar(const std::string str) const;
        /**
         Read value of the variable with name `str`
         
         - Parameter str: name of the variable to get
            
         - Returns: a reference to the mapped value of the element with key equivalent to key. If no such element exists, an exception of type std::out_of_range is thrown.
         */
        std::string getVar(const std::string str) const;
        /**
         Insert variable in the environment
         
         - Parameter key: name of the variable
         - Parameter value: value of the variable
         */
        void addVar(const std::string key, const std::string value);

    private:
        std::unordered_map<std::string, std::string> m_variables;
};
