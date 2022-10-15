#include <vector>

#include "token.h"
#include "commandData.h"

class Parser {
    public:
        Parser();
        ~Parser();

        std::vector<CommandData> parse(std::vector<Token> t);
};