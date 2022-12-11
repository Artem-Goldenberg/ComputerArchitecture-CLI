#include "io.h"

// Main function to run the whole shell

class Parser;
class Preprocessor;
class Lexer;
class CommandExecutor;
class Environment;

/**
 Command line abstraction.
 
 Activate with `runPipeline()` method.
    
 Reads the input string from `IO:getRequest` method, processes it and passes the resulting string into `IO::writeResponce` method.
 
 ```C++
 Shell sh();
 sh.runPipeline();
 
 // interact with shell using stdin, stdout, stderr
 ```
 */
class Shell {
    public:
        /**
         Creates all the neccessary processing components, including default `IO` member that
         writes to `stdout` and reads from `stdin`
         */
        Shell();
        
        ~Shell();
        
        /**
         Runs the interactive shell
         
         Returns when special `exit` string has been read from `IO::getRequest`
         */
        void runPipeline();
        
        /**
         Sets new `IO` instance for shell to get the input from and write the output to
         
         - Parameter newIO: Pointer to the new `IO` instance
         */
        void setIO(IO *newIO);
        
    private:
        Environment* m_env;
        IO* m_IO;
        Preprocessor* m_Preprocessor;
        Lexer* m_Lexer;
        Parser* m_Parser;
        CommandExecutor* m_CommandExecutor;
};
