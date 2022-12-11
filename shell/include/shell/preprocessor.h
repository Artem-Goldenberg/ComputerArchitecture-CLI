#include <string>

#include "result.h"
#include "environment.h"

/**
 Expands the `$var` variables and checks the quotes balance
 
 
 ```C++
 Environment env();
 env.addVar("idiot", "not interested in politics");
 
 Preprocessor p();
 std::string input = "I am $idiot";
 
 Result result = p.substitute(input, env);
 result.unwrap() // I am not interesetd in politics
 ```
 */
class Preprocessor {
    public:
        Preprocessor();
        ~Preprocessor();

        /**
         Performs the substitution of `$var` variables in the input string using the provided environment
         Checks the quotes balance as well
         
         If encounters a variable name after `$` which is not in the env, returns an `Error` case with that name
         in description
         
         If quotes in the input string are not balanced returns an `Error` case explaining that
         
         - Parameter in: Reference to the input string
         - Parameter env: Reference to the `Environment` instance, storing the expansion variables
         
         - Returns:  A `Result` instance with `Ok` and resulting string or `Error` and an error description string
         */
        Result substitute(const std::string &in, const Environment &env);
    private:
        const char varIndicator = '$';
        // array of variable name terminating characters
        // can be extended later
        const std::string varTerminators = " $";
};
