#include "io.h"

// Main function to run the whole shell

class Parser;
class Preprocessor;
class Lexer;
class CommandExecutor;
class Environment;

class Shell {
    public:
        Shell();
        ~Shell();
        void runPipeline();

        // set overloaded pipline members
        void setIO(IO *newIO);

    private:
        Environment* m_env;
        IO* m_IO;
        Preprocessor* m_Preprocessor;
        Lexer* m_Lexer;
        Parser* m_Parser;
        CommandExecutor* m_CommandExecutor;
};