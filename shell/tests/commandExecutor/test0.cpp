#include "commandExecutor.h"
#include <iostream>

int main() {
    std::cout << "CommandExecutor test 0 start:" << std::endl;
    
    CommandData echo("echo");
    echo.addArgument("something");
    
    Pipe* pipe = new Pipe();
    std::shared_ptr<Pipe> p(pipe);
    echo.setOutputPipe(p);
    
    CommandData wc("wc");
    wc.setInputPipe(p);
    
    std::vector<CommandData> data;
    data.push_back(echo);
    data.push_back(wc);
    
    Environment env;
    CommandExecutor e(&env);
    Result res = e.process(data);
    
    std::cout << "CommandExecutor test 0 end" << std::endl;
    
    if (!res.isOk()) return 1;
    if (res.unwrap() != "1 1 9") return 1;
    return 0;
}
