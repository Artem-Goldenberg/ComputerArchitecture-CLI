#include <string>

#include "result.h"
#include "environment.h"

class Preprocessor {
    public:
        Preprocessor();
        ~Preprocessor();

        Result substitute(const std::string &in, const Environment &env);
    private:
        const char varIndicator = '$';
        /// array of variable name terminating characters
        /// can be extended later
        const std::string varTerminators = " $";
};