#include <vector>
#include <regex>
#include <variant>

#include "result.h"
#include "environment.h"

/// Base class for all commands in `Shell`.
class Command {
    public:
        Command();
        virtual ~Command() = default;

        /**
         Represents an act of running the command in `Shell`
         
         Subclasses should override this method to make themselves useful
         
         - Parameter args: arguments passed in the command line after the command name
         - Parameter input: string representing stdin of the command
         
         - Returns: `Result` of invoking the command.
         */
        virtual Result execute(std::vector<std::string> args, std::string input) = 0;
};

class AssigmentCommand : public Command {
    public:
        AssigmentCommand(Environment *env);
        ~AssigmentCommand();

        Result execute(std::vector<std::string> args, std::string input) override;
    
    private:
        Environment* m_env;
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
