#include "command.h"
#include "argh.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iterator>
#include <cstring>

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

static std::string joinAll(std::vector<std::string> args, std::string input = "") {
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
    if (ec) return Result(Error, filename + ": " + ec.message());
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
    std::string commandString = "";
    // add input to the external command via echo "input" | cmd
    if (!input.empty()) commandString += "echo \"" + input + "\" | ";
    
    commandString += joinAll(args);
    commandString += " 2>&1"; // stderr -> stdout
    
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
 ///////////////////////// CAT //////////////////////////////////////
////////////////////////////////////////////////////////////////////

Cat::Cat() {}

Cat::~Cat() {}

Result Cat::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() ) {
        if( input.empty()) {
            return NOT_ENOUGH_ARGS;
        } else {
            return Result(Ok, input);
        }
    }

    std::string ans = "";

    for (auto arg : args) {
        Result res = read(arg);
        if (!res.isOk()) return res;
        ans += res.unwrap();
    }
    
    if(!ans.empty()) ans.pop_back();

    return Result(Ok, ans);
}

Result Cat::read(std::string filename) {
    Result res = isFileOk(filename);
    if (!res.isOk()) return res;
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return Result(Error, "Unable to open the file: " + filename);
    std::string content{std::istreambuf_iterator{ifs}, {}};
    ifs.close();
    return Result(Ok, content);
}


  ///////////////////////////////////////////////////////////////////////
 ///////////////////////// ECHO ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


Echo::Echo() {}

Echo::~Echo() {}

Result Echo::execute(std::vector<std::string> args, std::string input) {
    if (args.empty() && input.empty()) return NOT_ENOUGH_ARGS;
    
    std::string ans = joinAll(args, input);
    
    return Result(Ok, ans);
}


  ////////////////////////////////////////////////////////////////////
 ///////////////////////// WORD COUNT  //////////////////////////////
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
    } else {
        ans.resize(ans.size()-1); // delete extra '\n' char
    }
    
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
 ///////////////////////// PWD  /////////////////////////////////////
////////////////////////////////////////////////////////////////////

Pwd::Pwd() {}

Pwd::~Pwd() {}

Result Pwd::execute(std::vector<std::string> args, std::string input) {
    if (!args.empty() || !input.empty()) return Result(Error, "Too many arguments");
    auto path = std::filesystem::current_path();
    return Result(Ok, path.string());
}

  ////////////////////////////////////////////////////////////////////
 ///////////////////////// GREP  ////////////////////////////////////
////////////////////////////////////////////////////////////////////

Grep::Grep() {}

Grep::~Grep() {}

Result Grep::execute(std::vector<std::string> args, std::string input) {
    if (args.empty()) return NOT_ENOUGH_ARGS;
    
    auto var = parse(args);
   
    if (std::holds_alternative<std::string>(var))
        return Result(Error, std::get<std::string>(var));
    
    if (!std::holds_alternative<ParseResult>(var))
        return Result(Error, "Unkown error");
    
    auto [posArgs, caseInsensetive, wordsOnly, num_lines] = std::get<ParseResult>(var);
    if (posArgs.empty()) return NOT_ENOUGH_ARGS;
    
    std::string result;
    bool prependFilename = posArgs.size() > 2;
    
    auto argit = posArgs.begin();
    
//    std::string sanitized = escapeSpecialChars(*argit);
    std::string sanitized = *argit;
    auto options = caseInsensetive ? std::regex::icase : std::regex::ECMAScript;
    std::string query_str = wordsOnly ? "\\b" + sanitized + "\\b" : sanitized;
    std::regex query(query_str, options);
    
    if (posArgs.size() == 1) {
        if (input.empty()) return NOT_ENOUGH_ARGS;
        else return find(query, input, false, num_lines);
    }
    
    for (++argit; argit != posArgs.end(); ++argit) {
        Result ans = find(query, *argit, true, num_lines, prependFilename);
        if (!ans.isOk()) return ans;
        
        result += ans.unwrap();
        
        if (prependFilename) {
            if (argit + 1 == posArgs.end() && ans.unwrap().empty()) {
                // if found nothing and on the last iteration then remove '--\n' from the previous iteration
                // we may not have it only if all result is empty in which case just skip and return empty string
                if (!result.empty())
                    result.erase(result.end() - 3, result.end());
            } else if (argit + 1 != posArgs.end() && !ans.unwrap().empty())
                result += "--\n";
        }
    }
    
    return Result(Ok, result);
}

std::string Grep::escapeSpecialChars(std::string s) {
    static const char specialChars[] = R"(.^$+()[]{}|?*)";
    std::string out;
    out.reserve(s.size());
    for (auto ch : s) {
        if (std::strchr(specialChars, ch))
            out.push_back('\\');
        out.push_back(ch);
    }
    return out;
}

std::variant<Grep::ParseResult, std::string> Grep::parse(std::vector<std::string> args) {
    std::vector<const char*> cargs;
    cargs.reserve(args.size());
    
    for (const std::string &str : args)
        if (!str.empty()) // по идеи аргументы не могут быть пустыми, но мало ли
            cargs.push_back(&str.front());
    
    argh::parser parser;
    parser.add_param("A");
    parser.parse((int)cargs.size(), cargs.data(), argh::parser::SINGLE_DASH_IS_MULTIFLAG);
    
    bool caseInsensetive = false;
    bool wordsOnly = false;
    int num_lines = 0;
    
    for (auto& flag : parser.flags()) {
        if (flag.empty()) continue;
        switch (flag[0]) {
            case 'i':
                caseInsensetive = true;
                break;
            case 'w':
                wordsOnly = true;
                break;
            default:
                return "Unknown flag: " + flag;
        }
    }

    for (auto& param : parser.params()) {
        if (param.first == "A") {
            if (std::istringstream(param.second) >> num_lines) {
                if (num_lines < 0)
                    return "Number of lines must be a non-negative number, got: " + param.second;
            } else
                return "Number of lines must be an integer, got: " + param.second;
        } else
            return "Unknown parameter: " + param.first;
    }
    
    return (ParseResult){parser.pos_args(), caseInsensetive, wordsOnly, num_lines};
}

Result Grep::find(std::regex query,
                  std::string string,
                  bool isFile,
                  int num_lines,
                  bool prependFilename) {
    std::string result;
    if (isFile) {
        Result res = isFileOk(string);
        if (!res.isOk()) return res;
        
        std::ifstream file(string);
        
        if (!file.good()) return Result(Error, "File not found: " + string);
        
        result = findIn(query, file, num_lines, prependFilename ? string : "");
        
        file.close();
    } else {
        std::istringstream s(string);
        result = findIn(query, s, num_lines, "");
    }
    return Result(Ok, result);
}

std::string Grep::findIn(std::regex query,
                         std::istream &input,
                         int num_lines,
                         std::string optionalPrefix) {
    int linesToPrint = 0;
    std::string result;
    std::string line;
    
    while (getline(input, line)) {
        if (std::regex_search(line, query)) {
            if (!optionalPrefix.empty()) result += optionalPrefix + ": ";
            result += line + "\n";
            linesToPrint = num_lines;
        } else if (linesToPrint > 0) {
            if (!optionalPrefix.empty()) result += optionalPrefix + "- ";
            result += line + "\n";
            linesToPrint--;
        }
    }
    
    return result;
}

  ////////////////////////////////////////////////////////////////////
 ///////////////////////// EXIT /////////////////////////////////////
////////////////////////////////////////////////////////////////////

Exit::Exit() {}

Exit::~Exit() {}

Result Exit::execute(std::vector<std::string> args, std::string input) {
    return Result(Error, "_EXIT");
}
