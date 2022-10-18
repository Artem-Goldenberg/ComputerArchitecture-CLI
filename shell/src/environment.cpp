#include "environment.h"

Environment::Environment() {}

Environment::~Environment() {}

bool Environment::findVar(const std::string str) const {
    return m_variables.find(str) != m_variables.end();
}

std::string Environment::getVar(const std::string str) const {
    return m_variables.at(str);
}