#include "commandExecutor.h"
#include <iostream>

using namespace std;

int main() {
    cout << "CommandExecutor test 0 start:\n";
    
    CommandData echo("echo");
    echo.addArgument("something");
    
    Pipe* pipe = new Pipe();
    shared_ptr<Pipe> p(pipe);
    echo.setOutputPipe(p);
    
    CommandData wc("wc");
    wc.setInputPipe(p);
    
    vector<CommandData> data;
    data.push_back(echo);
    data.push_back(wc);
    
    Environment env;
    CommandExecutor e(&env);
    Result res = e.process(data);
    
    cout << "CommandExecutor test 0 end\n";
    
    if (!res.isOk()) return 1;
    if (res.unwrap() != "1 1 9") return 1;
    return 0;
}
