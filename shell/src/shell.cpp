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
        
        Result processed = m_Preprocessor->substitute(req, *m_env);
        
        if(req == "exit") break; // TODO: normal pipeline
        
        if (processed.isOk()) m_IO->writeResponce(processed.unwrap());
        else m_IO->writeResponce("The error occured while processing: " + processed.unwrap());
    }
}


void Shell::setIO(IO *newIO) {
    m_IO = newIO;
}
