#include "command.h"
#include "commandData.h"

class CommandExecutor {
    public:
        CommandExecutor(Environment* env);
        ~CommandExecutor();

        Result process(std::vector<CommandData> e);

    private:
        ExternalCommand* external;
        std::unordered_map<std::string, Command*> commands;
};
