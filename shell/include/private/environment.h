#include <string>
#include <unordered_map>

#pragma once

class Environment {
    public:
        Environment();
        ~Environment();

        bool findVar(const std::string str) const;
        std::string getVar(const std::string str) const;

    private:
        std::unordered_map<std::string, std::string> m_variables;
};