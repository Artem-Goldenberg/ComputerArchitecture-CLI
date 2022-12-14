#include "preprocessor.h"

int main() {
    Environment env;
    env.addVar("test_p", "p");
    env.addVar("test_wd", "wd");
    Preprocessor p;
    Result res = p.substitute(" $test_p$test_wd", env);
    if (res.isOk() && res.unwrap()  == " pwd")
        return 0;
    return 1;
}
