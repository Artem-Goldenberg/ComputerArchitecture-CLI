#include "commandExecutor.h"

CommandExecutor::CommandExecutor(Environment* env) {
    auto assCmd = new AssigmentCommand(env);
    auto extCmd = new ExternalCommand;
    auto cat = new Cat();
    auto echo = new Echo();
    auto wc = new WordCount();
    auto pwd = new Pwd();
    auto ext = new Exit();
    
    commands.insert(std::make_pair("assignment", assCmd));
    commands.insert(std::make_pair("external", extCmd));
    commands.insert(std::make_pair("cat", cat));
    commands.insert(std::make_pair("echo", echo));
    commands.insert(std::make_pair("wc", wc));
    commands.insert(std::make_pair("pwd", pwd));
    commands.insert(std::make_pair("exit", ext));
}

CommandExecutor::~CommandExecutor() {
    for (auto const& [name, cmd] : commands) {
        delete cmd;
    }
}

Result CommandExecutor::process(std::vector<CommandData> e) {
    // TODO
    return Result(Error, "TODO");
}
