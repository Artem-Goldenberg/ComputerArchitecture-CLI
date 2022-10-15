#include "command.h"

  ////////////////////////////////////////////////////////////////////
 //////////////////////// ASSIGMENT COMMAND /////////////////////////
////////////////////////////////////////////////////////////////////

AssigmentCommand::AssigmentCommand(Environment *env) : m_env(env) {}

AssigmentCommand::~AssigmentCommand() {
    delete m_env;
}

Result AssigmentCommand::execute(std::vector<std::string> args, std::string input) {
    // TODO : add data to the m_env
    return Result(Ok, "");
}

  ////////////////////////////////////////////////////////////////////
 ///////////////////////// EXTERNAL COMMAND /////////////////////////
////////////////////////////////////////////////////////////////////

ExternalCommand::ExternalCommand() {}

ExternalCommand::~ExternalCommand() {}

Result ExternalCommand::execute(std::vector<std::string> args, std::string input) {
    std::string ans;

    // TODO: call utility from path or whatewer

    return Result(Error, "TODO");
}