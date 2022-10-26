#include <string>
#include <unordered_map>
#include <string_view>

#pragma once

class Environment {
    public:
        Environment();
        ~Environment();

        bool findVar(const std::string str) const;
        std::string getVar(const std::string str) const;
        void addVar(const std::string key, const std::string value);

    private:
        std::unordered_map<std::string, std::string> m_variables;
};