#include "commandData.h"

  ////////////////////////////////////////////////////////////////////
 /////////////////////////////// PIPE ///////////////////////////////
////////////////////////////////////////////////////////////////////

Pipe::Pipe() {}

Pipe::~Pipe() {}

std::string Pipe::read() {
    return m_data;
}

void Pipe::write(std::string s) {
    m_data = s;
}

  ////////////////////////////////////////////////////////////////////
 ////////////////////////// COMMAND DATA ////////////////////////////
////////////////////////////////////////////////////////////////////

CommandData::CommandData() {}

CommandData::CommandData(std::string name) : m_name(name) {}

CommandData::CommandData(Pipe* p) : m_input(p) {}

CommandData::~CommandData() {
    delete m_input;
    delete m_output;
}

void CommandData::setName(std::string name) {
    m_name = name;
}

void CommandData::addArgument(std::string arg) {
    m_args.push_back(arg);
}

void CommandData::setInputPipe(Pipe* p) {
    m_input = p;
}

void CommandData::setOutputPipe(Pipe* p) {
    m_output = p;
}

std::string CommandData::getName() {
    return m_name;
}

std::vector<std::string> CommandData::getArgs() {
    return m_args;
}
