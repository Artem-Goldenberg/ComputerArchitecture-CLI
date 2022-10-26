#include <string>
#include <vector>

#pragma once

class Pipe {
    public:
        Pipe();
        ~Pipe();

        std::string read();
        void write(std::string s);

    private:
        // but data can be whatever you want
        std::string m_data;
};


class CommandData {
    public:
        CommandData();
        CommandData(std::string name);
        CommandData(Pipe* p);
        ~CommandData();

        void setName(std::string name);
        void addArgument(std::string arg);
        void setInputPipe(Pipe* p);
        void setOutputPipe(Pipe* p);

        std::string getName();
        std::vector<std::string> getArgs();

    private:
        std::string m_name;
        std::vector<std::string> m_args;
        Pipe* m_input = nullptr;
        Pipe* m_output = nullptr;
};