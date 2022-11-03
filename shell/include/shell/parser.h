#include <vector>
#include <variant>

#include "token.h"
#include "commandData.h"

class Parser {
    public:
        Parser();
        ~Parser();

        std::variant<std::vector<CommandData>, std::string> parse(std::vector<Token> t);
};