#include "shell.h"

#include "lexer.h"
#include "commandExecutor.h"
#include "preprocessor.h"
#include "parser.h"
#include "environment.h"

Shell::Shell() :
    m_env(new Environment()),
    m_IO(new IO()),
    m_Preprocessor(new Preprocessor()),
    m_Lexer(new Lexer()),
    m_Parser(new Parser()),
    m_CommandExecutor(new CommandExecutor(m_env)) {}

Shell::~Shell() {
    delete m_IO;
    delete m_env;
    delete m_CommandExecutor;
    delete m_Parser;
    delete m_Lexer;
    delete m_Preprocessor;
}

void Shell::runPipeline() {
    // MAIN LOOP
    while(true) {
        std::string req = m_IO->getRequest();

        if(req == "exit") break; // TODO: normal pipeline

        m_IO->writeResponce(req);
    }
}

void Shell::setIO(IO *newIO) {
    m_IO = newIO;
}
