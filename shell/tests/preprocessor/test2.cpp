#include "preprocessor.h"

int main() {
    Environment env;
    env.addVar("varN", "varV");
    Preprocessor p;
    Result res = p.substitute("$varN", env);
    if (res.isOk() && res.unwrap()  == "varV")
        return 0;
    return 1;
}
