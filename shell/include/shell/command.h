#include <vector>
#include <regex>
#include <variant>

#include "result.h"
#include "environment.h"

class Command {
    public:
        Command();
        virtual ~Command() = default;

        virtual Result execute(std::vector<std::string> args, std::string input) = 0;
};

class AssigmentCommand : public Command {
    public:
        AssigmentCommand(Environment *env);
        ~AssigmentCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        Environment* m_env;
    
        bool validate(std::string name);
};

class ExternalCommand : public Command {
    public:
        ExternalCommand();
        ~ExternalCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
};

class Cat : public Command {
    public:
        Cat();
        ~Cat();

        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        Result read(std::string filename);
};

class Echo : public Command {
    public:
        Echo();
        ~Echo();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

class WordCount : public Command {
    public:
        WordCount();
        ~WordCount();
    
        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        std::tuple<Result, int, int, int> countWords(std::string string, bool isFile);
        std::tuple<int, int, int> countIn(std::istream&);
};

class Pwd : public Command {
    public:
        Pwd();
        ~Pwd();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

class Grep : public Command {
    public:
        Grep();
        ~Grep();
        
        Result execute(std::vector<std::string> args, std::string input) override;
    private:
        typedef std::tuple<std::vector<std::string>, bool, bool, int> ParseResult;
    
        std::variant<ParseResult, std::string> parse(std::vector<std::string> args);
    
        Result find(std::regex query,
                    std::string string,
                    bool isFile,
                    int num_lines = 0,
                    bool prependFilename = false);
    
        std::string findIn(std::regex query,
                           std::istream &input,
                           int num_lines,
                           std::string optionalPrefix);
    
        std::string escapeSpecialChars(std::string str);
};

class Exit : public Command {
    public:
        Exit();
        ~Exit();
    
        Result execute(std::vector<std::string> args, std::string input) override;
};

