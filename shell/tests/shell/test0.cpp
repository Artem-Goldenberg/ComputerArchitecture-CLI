#include "shell/shell.h"

#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

int main() {

    int in_shell_pipe[2];
    int out_shell_pipe[2];
    if(pipe(in_shell_pipe) == -1) {
        std::cout << "Cannot instantiate in_pipe" << std::endl;
        return 1;
    }
    if(pipe(out_shell_pipe) == -1) {
        std::cout << "Cannot instantiate out_pipe" << std::endl;
        return 1;
    }

    pid_t pid;
    pid = fork();
    if( pid == -1 ) {
        std::cout << "Failed to fork" << std::endl;
        return 2;
    }

    if( pid == 0 ) { // child
        dup2(in_shell_pipe[0], STDIN_FILENO); // redirect stdin
        dup2(out_shell_pipe[1], STDOUT_FILENO); // redirect stdout

        close(in_shell_pipe[1]);
        close(out_shell_pipe[0]);

        Shell myShell;
        myShell.runPipeline();

        close(in_shell_pipe[0]);
        close(out_shell_pipe[1]);
    } else { // parent
        close(in_shell_pipe[0]);
        close(out_shell_pipe[1]);

        // query
        std::vector<std::string> input = {"echo \"lol\"\n", "exit\n"};
        std::string true_ans = "";


        // insert to query
        for( int iter = 0 ; iter < input.size(); iter++ ) {
            write(in_shell_pipe[1], input[iter].c_str(), input[iter].size()+1);
            // write(in_shell_pipe[1], "\n", 2);
        }
        close(in_shell_pipe[1]);
        std::cout << "Input sent" << std::endl;


        // await
        int status;
        wait(&status);
        std::cout << "Wait status: " << status << std::endl;


        // get response
        std::string ans = "";
        char reading_buf[1];
        int bound = 100;
        while(read(out_shell_pipe[0], reading_buf, 1) > 0 && bound > 0) {
            ans += reading_buf[0];
            bound--;
        }
        close(out_shell_pipe[0]);
        std::cout << "Response captured:\n\"" << ans << "\"" << std::endl;


        //check responce
        if( ans != true_ans ) {
            std::cout << "Got output:\n\"" << ans << "\",\nbut expected:\n\"" << true_ans << "\"" << std::endl;
            return 3;
        }
    }


    return 0;
}
