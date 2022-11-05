#include "command.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>

#define NOT_ENOUGH_ARGS Result(Error, "Not enough arguments")

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
    if (args.size() < 2) return NOT_ENOUGH_ARGS;
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
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    std::string ans;
    
    std::vector<std::string> copied(args);
    if (!input.empty()) copied.insert(copied.end(), input);
    
    for (std::string arg : copied) {
        Result res = read(arg);
        if (!res.isOk()) return res;
        ans += res.unwrap();
    }
    
    ans.pop_back();
    
    return Result(Ok, ans);
}

Result Cat::read(std::string filename) {
    std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
    
    auto fileSize = ifs.tellg();
    if (fileSize < 0)
        return Result(Error, "Unable to read the file: " + filename);
    
    ifs.seekg(0, std::ios::beg);
    
    std::vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);
    
    return Result(Ok, std::string(&bytes[0], fileSize));
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// ECHO ////////////////////////
///////////////////////////////////////////////////////////////////////

Echo::Echo() {}

Echo::~Echo() {}

Result Echo::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    std::stringstream s("", std::ios_base::ate | std::ios_base::in | std::ios_base::out);
    std::copy(args.begin(), args.end() - 1, std::ostream_iterator<std::string>(s, " "));
    s << args.back();
    if (!input.empty()) s << " " << input;
    
    return Result(Ok, s.str());
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// WORD COUNT  /////////////////////////
////////////////////////////////////////////////////////////////////

WordCount::WordCount() {}

WordCount::~WordCount() {}

Result WordCount::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    std::string ans;
    int totalCharCount = 0, totalWordCount = 0, totalLineCount = 0;
    bool printTotal = false; // if more than 2 files, print total in the end
    
    std::vector<std::string> copied(args);
    if (!input.empty()) copied.insert(copied.end(), input);
    
    for (std::string arg : copied) {
        auto [res, cc, wc, lc] = countWords(arg);
        if (!res.isOk()) return res;
        totalCharCount += cc;
        totalWordCount += wc;
        totalLineCount += lc;
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
    } else return {Result(Error, "File not found: " + filename), 0, 0, 0};
    
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
    if (!args.empty() || !input.empty()) return Result(Error, "Too many arguments");
    auto path = std::filesystem::current_path();
    return Result(Ok, path.string());
}

  ////////////////////////////////////////////////////////////////////
 ///////////////////////// EXIT /////////////////////////
////////////////////////////////////////////////////////////////////

Exit::Exit() {}

Exit::~Exit() {}

Result Exit::execute(std::vector<std::string> args, std::string input) {
    return Result(Error, "_EXIT");
}
