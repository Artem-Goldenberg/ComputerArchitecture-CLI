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


        // Query
        std::vector<std::string> input = {
            "prime-runn steam &", // just forgot that i have steam installed. Unexpectively opened it... Looks like a sign!
            "cat file_that_not_exist",
            "echo 'file_that_not_exist\"",
            "echo | cat",
            "exit"
        };
        std::string true_ans = "\n"
            "Welcome to myshell\n"
            "Shell> Shell> \n"
            "cat: file_that_not_exist: No such file or directory\n\n"
            "Shell> \n"
            "Quotes are not balanced\n\n"
            "Shell> \n"
            "echo: Not enough arguments\n\n"
            "Shell> \n"
            "Process exited\n";


        // Insert to query
        std::string query = "";
        for( int iter = 0 ; iter < input.size(); iter++ ) {
            query += input[iter] + "\n";
        }
        write(in_shell_pipe[1], query.c_str(), query.size()+1);
        close(in_shell_pipe[1]);
        std::cout << "Input sent" << std::endl;


        // Await
        int status;
        wait(&status);
        std::cout << "Wait status: " << status << std::endl;


        // Get response
        std::string ans = "";
        char reading_buf[1];

        while(read(out_shell_pipe[0], reading_buf, 1) > 0 ) {
            if ( reading_buf[0] == '\0') {
                std::cout << "Damn '\\0' characted found" << std::endl;
                ans += "[!!!]\n";
            } else {
                ans += reading_buf[0];
            }
        }
        close(out_shell_pipe[0]);
        // std::cout << "Response captured:\n\"" << ans << "\"" << std::endl;


        bool error_found = false;

        // Check responce
        if( ans.size() != true_ans.size() ) {
            std::cout << "Wrong answer size" << std::endl;
        }

        int line = 1, num = 0;
        for(int i =0; i < std::min(ans.size(), true_ans.size()); i++) {
            if (ans[i] == '\n') {
                line++;
                num = 0;
            } else {
                num++;
            }

            if( ans[i] != true_ans[i] ) {
                std::cout << "Diffenent char: " << i << " (line " << line << ", num " << num << ") is \"" << (int)ans[i] << "\" instead of \"" << (int)true_ans[i] << "\""<< std::endl;
                error_found = true;
            }
        }

        if( error_found ) {
            std::cout << "Got output:\n\"" << ans << "\",\nbut expected:\n\"" << true_ans << "\"" << std::endl;
            return 4;
        }
    }

    return 0;
}