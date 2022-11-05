#include <string>
#include <vector>
#include <memory>

#pragma once

class Pipe {
    public:
        Pipe();
        ~Pipe();

        std::string read();
        void write(std::string s);

    private:
        // but data can be whatever you want
        std::string m_data = "";
};


class CommandData {
    public:
        CommandData();
        CommandData(std::string name);
        CommandData(std::shared_ptr<Pipe> p);
        CommandData(const CommandData &other);
        ~CommandData();

        void setName(std::string name);
        void addArgument(std::string arg);
        void setInputPipe(std::shared_ptr<Pipe> p);
        void setOutputPipe(std::shared_ptr<Pipe> p);

        std::string getName();
        std::vector<std::string> getArgs();
        std::string getInput();
        std::string getOutput();
    
        void setOutput(std::string);

    private:
        std::string m_name;
        std::vector<std::string> m_args;
        std::shared_ptr<Pipe> m_input = nullptr;
        std::shared_ptr<Pipe> m_output = nullptr;
};
