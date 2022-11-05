#include "shell.h"

#include "lexer.h"
#include "commandExecutor.h"
#include "preprocessor.h"
#include "parser.h"
#include "environment.h"

#define SHELL_EXIT_SYMBOL "exit: _EXIT"

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

        Result ans_prep_res = m_Preprocessor->substitute(req, *m_env);
        if(!ans_prep_res.isOk()) {
            m_IO->writeResponce(ans_prep_res.unwrap());
            continue;
        }
        
        std::string ans_prep = ans_prep_res.unwrap();
        std::vector<Token> ans_lexer = m_Lexer->tokenize(ans_prep);
        std::variant<std::vector<CommandData>, std::string> ans_parse_var = m_Parser->parse(ans_lexer);
        if( std::holds_alternative<std::string>(ans_parse_var) ) {
            m_IO->writeResponce("ERROR: " + std::get<std::string>(ans_parse_var));
            continue;
        }
        
        std::vector<CommandData> ans_parse = std::get<std::vector<CommandData>>(ans_parse_var);
        
        Result ans_cmd_res = m_CommandExecutor->process(ans_parse);
        if (!ans_cmd_res.isOk()) {
            if (ans_cmd_res.unwrap() == SHELL_EXIT_SYMBOL) break;
            
            // mayber write Error: some or something ...
        }
        m_IO->writeResponce(ans_cmd_res.unwrap());
    }
}


void Shell::setIO(IO *newIO) {
    m_IO = newIO;
}
