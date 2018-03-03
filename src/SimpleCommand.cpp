#include <iostream>
#include <unistd.h>
#include "SimpleCommand.h"

void SimpleCommand::execute() {
    std::cout << "FIXME: You should change SimpleCommand::execute()" << std::endl;
    // FIXME: Your code here...

    if (command == "cd") {
        cd();
    } else if (command == "pwd") {
        pwd();
    } else if (command == "ls"){
        ls();
    }

}

void SimpleCommand::cd() {
    if (arguments.size() == 0) {
        chdir(getenv("HOME"));
    } else if(arguments.size() == 1){
        if (arguments[0] == "~"){
            chdir(getenv("HOME"));
        }
        const char * c = arguments[0].c_str();
        chdir(c);
    }
    pwd();
}



void SimpleCommand::pwd() {
    char buf[FILENAME_MAX];
    std::cout << getcwd(buf, FILENAME_MAX) << std::endl;
}

void SimpleCommand::ls() {
    if (arguments.size() == 0){
        char *args[] = {"ls", NULL};
        execvp("ls", args);
    }else if(arguments.size() == 1) {
        if (arguments[0] == "-l") {
            char *args[] = {"ls", "-l", NULL};
            execvp("ls", args);
        } else if (arguments[0] == "-a") {
            char *args[] = {"ls", "-a", NULL};
            execvp("ls", args);
        }
    }
}

