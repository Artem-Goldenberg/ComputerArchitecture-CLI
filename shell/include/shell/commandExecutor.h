#include "command.h"
#include "commandData.h"

 /// Manager that invokes requested commands with correct arguments and inputs, creating the end `Result`.
class CommandExecutor {
    public:
        /**
         Initializes `CommandExecutor` with specifyed `Environment`
     
         - Parameter env: Pointer to the shell `Environment` instace. Can be read and modified by some commands
         */
        CommandExecutor(Environment* env);
        ~CommandExecutor();

        /**
         Converts a sequence of prelinked pipeline commands into the final output.
         
         Finds implementation of each provided command name, returns error if fails to find one
         
         Execute each command starting from the first one in the pipeline, providing ouput for the next command
         If any of the commands fail, return the error description
         
         When all commands have been executed, returns ouput of the final command as `Result`
         
         - Parameter e: Vector of `CommandData` instances.
         It is important to correctly configure input and output `Pipe` of each instance before calling this method
         
         - Returns: The `Result` instance with `Ok` and final string from evaluating the pipeline, or
         `Error` and an error description string if something went wrong.
         */
        Result process(std::vector<CommandData> e);

    private:
        ExternalCommand* external;
        std::unordered_map<std::string, Command*> commands;
};
