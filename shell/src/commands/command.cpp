#include "command.h"
#include <algorithm>
#include <fstream>

#define NOT_ENOUGH_ARGS "Not enough arguments"

  ////////////////////////////////////////////////////////////////////
 //////////////////////// COMMAND ///////////////////////////////////
////////////////////////////////////////////////////////////////////

Command::Command() {}

Command::~Command() {}

  ////////////////////////////////////////////////////////////////////
 //////////////////////// ASSIGMENT COMMAND /////////////////////////
////////////////////////////////////////////////////////////////////

AssigmentCommand::AssigmentCommand(Environment *env) : m_env(env) {}

AssigmentCommand::~AssigmentCommand() {}

Result AssigmentCommand::execute(std::vector<std::string> args, std::string input) {
    if (args.size() < 2) return Result(Error, NOT_ENOUGH_ARGS);
    if (validate(args[0]) && validate(args[1]))
        m_env->addVar(args[0], args[1]);
    return Result(Ok, "");
}

bool AssigmentCommand::validate(std::string name) {
    if (name.empty()) return false;
    if (!isalpha(name[0])) return false;
    auto it = std::find_if_not(name.begin() + 1, name.end(), ::isalnum);
    return it == name.end();
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

  ////////////////////////////////////////////////////////////////////
 ///////////////////////// CAT /////////////////////////
////////////////////////////////////////////////////////////////////

Cat::Cat() {}

Cat::~Cat() {}

Result Cat::execute(std::vector<std::string> args, std::string input) {
    std::string ans;
    
    // TODO: call utility from path or whatewer
    
    return Result(Error, "TODO");
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// ECHO ////////////////////////
///////////////////////////////////////////////////////////////////////

Echo::Echo() {}

Echo::~Echo() {}

Result Echo::execute(std::vector<std::string> args, std::string input) {
    std::string ans;
    
    // TODO: call utility from path or whatewer
    
    return Result(Error, "TODO");
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// WORD COUNT  /////////////////////////
////////////////////////////////////////////////////////////////////

WordCount::WordCount() {}

WordCount::~WordCount() {}

Result WordCount::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return Result(Error, NOT_ENOUGH_ARGS);
    
    std::string ans;
    int totalCharCount = 0, totalWordCount = 0, totalLineCount = 0;
    bool printTotal = false; // if more than 2 files, print total in the end
    
    for (std::string arg : args) {
        auto [res, cc, wc, lc] = countWords(arg);
        totalCharCount += cc;
        totalWordCount += wc;
        totalLineCount += lc;
        if (!res.isOk()) return res;
        if (!ans.empty()) printTotal = true;
        ans += res.unwrap() + '\n';
    }
    if (!input.empty()) {
        auto [res, cc, wc, lc] = countWords(input);
        totalCharCount += cc;
        totalWordCount += wc;
        totalLineCount += lc;
        if (!res.isOk()) return res;
        if (!ans.empty()) printTotal = true;
        ans += res.unwrap() + '\n';
    }
    if (printTotal) {
        ans += std::to_string(totalLineCount) + ' ' + std::to_string(totalWordCount) +
        ' ' + std::to_string(totalCharCount) + "  total";
    } else ans.pop_back(); // string last '\n'
    
    return Result(Ok, ans);
}

std::tuple<Result, int, int, int> WordCount::countWords(std::string filename) {
    std::ifstream file(filename);
    
    char ch;
    enum states { WHITESPACE, WORD };
    int state = WHITESPACE;
    int charCount = 0, wordCount = 0, lineCount = 0;
    
    if (file.is_open()) {
        while (file.read(&ch, 1)) {
            charCount++;
            if (ch == '\n') lineCount++;
            if (isspace(ch)) state = WHITESPACE;
            else if (state == WHITESPACE) {
                wordCount++;
                state = WORD;
            }
        }
        file.close();
    } else return {Result(Error, "File named not found: " + filename), 0, 0, 0};
    
    return {
        Result(Ok, std::to_string(lineCount) + ' ' + std::to_string(wordCount) + ' ' +
                   std::to_string(charCount) + "  " + filename),
        charCount, wordCount, lineCount
    };
}

////////////////////////////////////////////////////////////////////
 ///////////////////////// PWD  /////////////////////////
////////////////////////////////////////////////////////////////////

Pwd::Pwd() {}

Pwd::~Pwd() {}

Result Pwd::execute(std::vector<std::string> args, std::string input) {
    std::string ans;
    
    // TODO: call utility from path or whatewer
    
    return Result(Error, "TODO");
}

////////////////////////////////////////////////////////////////////
///////////////////////// EXIT  /////////////////////////
////////////////////////////////////////////////////////////////////

Exit::Exit() {}

Exit::~Exit() {}

Result Exit::execute(std::vector<std::string> args, std::string input) {
    std::string ans;
    
    // TODO: call utility from path or whatewer
    
    return Result(Error, "TODO");
}
