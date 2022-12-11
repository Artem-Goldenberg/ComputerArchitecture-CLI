#include <string>
#include <vector>
#include <memory>

#pragma once

/**
 Entity for handling the input output of shell commands
 
 Two commands input and output can be 'glued' together with a pipe.
 For example
 ```
 // define a command with name and args
 CommandData echo("echo");
 echo.addArgument("secret password 123");
 
 // create a pipe and assign as an output of an echo command
 std::shared_ptr<Pipe> p(new Pipe());
 echo.setOutputPipe(p);
 
 // create command ans assign a pipe to its input
 CommandData wc(p);
 ```
 Now when we execute `echo` command, `wc` will automatically recieve `echo`'s output as its input.
 */
class Pipe {
    public:
        Pipe();
        ~Pipe();

        /// Read a string from pipe
        std::string read();
        /// Write a string to a pipe
        void write(std::string s);

    private:
        // but data can be whatever you want
        std::string m_data = "";
};


/**
 Entity for storing all neccessary information about the shell command
 
 Can be connected to another commands via input and output pipes
 */
class CommandData {
    public:
        /**
         Default consturctor
            
         Initializes an instance with an empty name, 0 args and null pipes
         */
        CommandData();
        /// Sets name of the command
        CommandData(std::string name);
        /// Sets p as an input pipe of the command
        CommandData(std::shared_ptr<Pipe> p);
        /// Copy constructorr
        CommandData(const CommandData &other);
        /// Default destructor
        ~CommandData();

        /**
         Command name setter
         - Parameter name: new name to be set
         */
        void setName(std::string name);
    
        /**
         Adds an argument to potentially pass to the command
         - Parameter arg: *the* argument
         */
        void addArgument(std::string arg);
    
        /**
        Set an input to the command
         
         When command is invoked using this data, its input will be provided by this pipe
         - Parameter p: prointer to a `Pipe` to be set as an input
         */
        void setInputPipe(std::shared_ptr<Pipe> p);
    
        /**
        Set pipe for output of the command
         
         When command is invoked using this data, its output will be stored int this pipe
         - Parameter p: prointer to a `Pipe` to be set as an output
         */
        void setOutputPipe(std::shared_ptr<Pipe> p);

        /// - Returns: command's name
        std::string getName();
        /// - Returns: command's arguments
        std::vector<std::string> getArgs();
    
        /**
         Invokes a command's input pipe to yield a string
         
         - Returns: string which pipe yielded, empty string if pipe is null
         */
        std::string getInput();
    
        /**
         Invokes a command's output pipe to yield a string
         
         - Returns: string which pipe yielded, empty string if pipe is null
         */
        std::string getOutput();
    
        /**
         Writes to a command's output pipe
         
         If output pipe is null, creates one and writes the string to ti
         - Parameter str: output string to be set
         */
        void setOutput(std::string str);

    private:
        std::string m_name;
        std::vector<std::string> m_args;
        std::shared_ptr<Pipe> m_input = nullptr;
        std::shared_ptr<Pipe> m_output = nullptr;
};
