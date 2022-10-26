#include "preprocessor.h"

int main() {
    Environment env;
    env.addVar("varN", "varV");
    Preprocessor p;
    Result res = p.substitute("$varN", env);
    return res.isOk() && res.unwrap()  == "varV";
}
