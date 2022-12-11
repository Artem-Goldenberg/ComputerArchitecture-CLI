#include "commandData.h"
#include <iostream>

  ////////////////////////////////////////////////////////////////////
 /////////////////////////////// PIPE ///////////////////////////////
////////////////////////////////////////////////////////////////////

Pipe::Pipe() : m_data() {}

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

CommandData::CommandData(std::shared_ptr<Pipe> p) : m_input(p) {}

CommandData::CommandData(const CommandData &other) :
    m_input(other.m_input), // other.m_input == nullptr? nullptr : new Pipe(*other.m_input)),
    m_output(other.m_output), //  == nullptr? nullptr : new Pipe(*other.m_output)),
    m_name(other.m_name),
    m_args(other.m_args) {}

CommandData::~CommandData() {}

void CommandData::setName(std::string name) {
    m_name = name;
}

void CommandData::addArgument(std::string arg) {
    m_args.push_back(arg);
}

void CommandData::setInputPipe(std::shared_ptr<Pipe> p) {
    m_input = p;
}

void CommandData::setOutputPipe(std::shared_ptr<Pipe> p) {
    m_output = p;
}

std::string CommandData::getName() {
    return m_name;
}

std::vector<std::string> CommandData::getArgs() {
    return m_args;
}

std::string CommandData::getInput() {
    if (m_input) return m_input->read();
    return "";
}

std::string CommandData::getOutput() {
    if (m_output) return m_output->read();
    return "";
}

void CommandData::setOutput(std::string data) {
    if (!m_output) {
        auto raw = new Pipe();
        m_output = std::shared_ptr<Pipe>(raw);
    }
    m_output->write(data);
}
