#include <string>

#include "result.h"
#include "environment.h"

class Preprocessor {
    public:
        Preprocessor();
        ~Preprocessor();

        Result substitute(const std::string &in, const Environment &env);
};