#include "commandExecutor.h"

CommandExecutor::CommandExecutor(Environment* env) {
    external = new ExternalCommand();
    
    auto assCmd = new AssigmentCommand(env);
    auto cat = new Cat();
    auto echo = new Echo();
    auto wc = new WordCount();
    auto pwd = new Pwd();
    auto grep = new Grep();
    auto ext = new Exit();
    
    commands.insert(std::make_pair("=", assCmd));
    commands.insert(std::make_pair("cat", cat));
    commands.insert(std::make_pair("echo", echo));
    commands.insert(std::make_pair("wc", wc));
    commands.insert(std::make_pair("pwd", pwd));
    commands.insert(std::make_pair("grep", grep));
    commands.insert(std::make_pair("exit", ext));
}

CommandExecutor::~CommandExecutor() {
    for (auto const& [name, cmd] : commands) {
        delete cmd;
    }
    delete external;
}

Result CommandExecutor::process(std::vector<CommandData> e) {
    // input1 -> command1 -> output1 -> input2 -> command2 -> ....
    
    for (auto it = e.begin(); it != e.end(); ++it) {
        auto data = *it;
        auto name = data.getName();
        std::vector<std::string> args;
        Command *cmd;
        if (commands.find(name) != commands.end()) {
            cmd = commands.at(name);
            args = data.getArgs();
        } else {
            cmd = external;
            args = data.getArgs();
            args.insert(args.begin(), name);
            name = "External";
        }

        Result res = cmd->execute(args, data.getInput());

        if (!res.isOk()) {
            std::string errorMsg = name + ": " + res.unwrap();
            return Result(Error, errorMsg);
        }
        (*it).setOutput(res.unwrap());
    }

    return Result(Ok, e.back().getOutput());
}
