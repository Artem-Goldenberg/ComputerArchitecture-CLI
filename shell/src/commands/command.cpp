#include "command.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>

#ifdef WINDOWS
#define popen _popen  // a hack?
#endif
#ifdef _WIN32
#define popen _popen
#endif
#ifdef _WIN64
#define popen _popen
#endif

#define NOT_ENOUGH_ARGS Result(Error, "Not enough arguments")

static std::string joinAll(std::vector<std::string> args, std::string input) {
    if (args.empty()) return input;
    std::stringstream s("", std::ios_base::ate | std::ios_base::in | std::ios_base::out);
    std::copy(args.begin(), args.end() - 1, std::ostream_iterator<std::string>(s, " "));
    s << args.back();
    if (!input.empty()) s << " " << input;
    return s.str();
}

static Result isFileOk(std::string filename) {
    const std::filesystem::path path(filename); // Constructing the path from a string is possible.
    std::error_code ec; // For using the non-THROWING overloads of functions below.
    if (std::filesystem::is_directory(path, ec)) return Result(Error, filename + " is a directory");
    if (ec) return Result(Error, ec.message());
    return Result(Ok, "");
}

////////////////////////////////////////////////////////////////////
 //////////////////////// COMMAND ///////////////////////////////////
////////////////////////////////////////////////////////////////////

Command::Command() {}

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
    std::string commandString = joinAll(args, input);
    std::string response;

    FILE *pipe;
    pipe = popen(commandString.c_str(), "r");
    
    if (!pipe) return Result(Error, "Unable to execute an external command");
    
    int bufSize = 100;
    char buffer[bufSize];
    while (fgets(buffer, bufSize, pipe) != NULL)
        response += buffer;
    
    pclose(pipe);

    return Result(Ok, response);
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
    Result res = isFileOk(filename);
    if (!res.isOk()) return res;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return Result(Error, "Unable to open the file: " + filename);
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();
    return Result(Ok, content);
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// ECHO ////////////////////////
///////////////////////////////////////////////////////////////////////

Echo::Echo() {}

Echo::~Echo() {}

Result Echo::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    std::string ans = joinAll(args, input);
    
    return Result(Ok, ans);
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// WORD COUNT  /////////////////////////
////////////////////////////////////////////////////////////////////

WordCount::WordCount() {}

WordCount::~WordCount() {}

Result WordCount::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    // Если есть аргументы, то забиваем на input, если нет, то считаем символы в input
    if (args.empty()) {
        auto [res, cc, wc, lc] = countWords(input, false);
        return res;
    }
    
    std::string ans;
    int totalCharCount = 0, totalWordCount = 0, totalLineCount = 0;
    bool printTotal = false; // if more than 2 files, print total in the end
    
    for (std::string arg : args) {
        auto [res, cc, wc, lc] = countWords(arg, true);
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

std::tuple<Result, int, int, int> WordCount::countWords(std::string string, bool isFile) {
    int charCount, wordCount, lineCount;
    if (isFile) {
        Result res = isFileOk(string);
        if (!res.isOk()) return {res, 0, 0, 0};
        
        std::ifstream file(string);
        
        if (!file.is_open()) return {Result(Error, "File not found: " + string), 0, 0, 0};
        
        auto [cc, wc, lc] = countIn(file);
        file.close();
        
        charCount = cc;
        wordCount = wc;
        lineCount = lc;
    } else {
        std::istringstream s(string);
        auto [cc, wc, lc] = countIn(s);
        charCount = cc;
        wordCount = wc;
        lineCount = lc;
    }
    
    return {
        Result(Ok, std::to_string(lineCount) + ' ' + std::to_string(wordCount) + ' ' +
                   std::to_string(charCount) + (isFile ? "  " + string : "")),
        charCount, wordCount, lineCount
    };
}

std::tuple<int, int, int> WordCount::countIn(std::istream &in) {
    char ch;
    enum states { WHITESPACE, WORD };
    int state = WHITESPACE;
    int charCount = 0, wordCount = 0, lineCount = 0;
    while (in.read(&ch, 1)) {
        if (lineCount == 0) lineCount++; // если есть хоть 1 смвол, засчитываем 1 строку
        charCount++;
        if (ch == '\n') lineCount++;
        if (isspace(ch)) state = WHITESPACE;
        else if (state == WHITESPACE) {
            wordCount++;
            state = WORD;
        }
    }
    if (ch == '\n') lineCount--; // не считаем строку если она последняя в файле и пустая
    return {charCount, wordCount, lineCount};
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
