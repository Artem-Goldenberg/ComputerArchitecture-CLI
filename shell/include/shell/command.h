#include <vector>

#include "result.h"
#include "environment.h"

class Command {
    public:
        Command();
        ~Command();

        virtual Result execute(std::vector<std::string> args, std::string input) = 0;
};

class AssigmentCommand : public Command {
    public:
        AssigmentCommand(Environment *env);
        ~AssigmentCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        Environment* m_env;
    
        bool validate(std::string name);
};

class ExternalCommand : public Command {
    public:
        ExternalCommand();
        ~ExternalCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
};

class Cat : public Command {
    public:
        Cat();
        ~Cat();

        Result execute(std::vector<std::string> args, std::string input) override;
};

class Echo : public Command {
    public:
        Echo();
        ~Echo();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

class WordCount : public Command {
    public:
        WordCount();
        ~WordCount();
    
        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        std::tuple<Result, int, int, int> countWords(std::string filename);
};

class Pwd : public Command {
    public:
        Pwd();
        ~Pwd();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

class Exit : public Command {
    public:
        Exit();
        ~Exit();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

