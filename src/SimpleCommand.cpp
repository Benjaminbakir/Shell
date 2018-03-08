#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>
#include "SimpleCommand.h"

void SimpleCommand::execute() {
    //std::cout << "FIXME: You should change SimpleCommand::execute()" << std::endl;
    // FIXME: Your code here...



    if (command == "cd") {
        cd();
    } else if (command != "") {
        int isChild = fork();
        if (redirects.empty() && isChild == 0) {
            execCmd();
        }
    } else {
        printf("Unknown command!\n");

    }

}

void SimpleCommand::cd() {
    if (arguments.size() == 0) {
        chdir(getenv("HOME"));
    } else if (arguments.size() == 1) {
        if (arguments[0] == "~") {
            chdir(getenv("HOME"));
        }
        const char *c = arguments[0].c_str();
        chdir(c);
    }

}

void SimpleCommand::execCmd() {
    std::vector<char *> arg;
    char *c = new char(command.length() + 1);
    strcpy(c, command.c_str());
    arg.push_back(c);
    for (std::string args : arguments) {

        char *ar = new char(args.length() + 1);
        strcpy(ar, args.c_str());
        arg.push_back(ar);
    }
    arg.push_back(NULL);
    execvp(c, &arg[0]);
}


void IORedirect::execute() {
    if (type == OUTPUT) {
        std::cout << "Output" << std::endl;

    } else if (type == APPEND) {

    } else if (type == INPUT) {


    }

}
