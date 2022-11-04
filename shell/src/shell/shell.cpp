#include "shell.h"

// temporal include
#include <iostream>

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

        if(req == "exit") break;
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

        {
            std::cout << "Your command is:" << std::endl;
            for(int cmd_len = 0; cmd_len < ans_parse.size(); cmd_len++) {
                std::cout << cmd_len+1 << ". Command name: \"" << ans_parse[cmd_len].getName() << "\"" << std::endl;
                for(int arg_num = 0; arg_num < ans_parse[cmd_len].getArgs().size(); arg_num++) {
                    std::cout << "  " << cmd_len+1 << "." << arg_num+1 << ". arg: \"" << ans_parse[cmd_len].getArgs()[arg_num] << "\"" << std::endl;
                }
            }
            m_IO->writeResponce("");
        }
        // TODO: normal command execution
    }
}


void Shell::setIO(IO *newIO) {
    m_IO = newIO;
}
