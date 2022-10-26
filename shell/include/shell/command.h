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
};

class ExternalCommand : public Command {
    public:
        ExternalCommand();
        ~ExternalCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
};