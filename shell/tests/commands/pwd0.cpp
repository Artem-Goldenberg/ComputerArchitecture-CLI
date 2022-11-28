#include "command.h"
#include <iostream>

int main() {
    std::cout << "Pwd test 0 start:\n";
    
    Pwd cmd;
    Result res = cmd.execute({}, "");
    std::cout << "Got path: " << (res.unwrap().c_str()) << std::endl;
    
    std::cout << "Pwd test 0 end\n";
    if (!res.isOk()) return 1;

    FILE *pipe;
    pipe = popen("pwd", "r");
    
    if (!pipe) return 1;
    
//    fprintf(pipe, "w\n");
    char* buffer = NULL;
    size_t bufferSize = 0;
    size_t line_size = getline(&buffer, &bufferSize, pipe);
    
    if (line_size == 0) return 1;
    
    std::string path(buffer);
    path.pop_back();
    
    free(buffer);
    pclose(pipe);
    
    std::cout << "Path we want: " << path << std::endl;
    
    if (res.unwrap() != path) return 1;
    return 0;
}
