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
    } else if(command=="pwd"){
        pwd();

    }else if(command=="exit"){
        std::cout<< "Okay see you soon!" << std::endl;
        exit(0);
    }
    else if (command != "") {

        if (redirects.empty()) {
            execCmd();
        } else {
            for (auto ioRedirect : redirects) {
                if (ioRedirect.getType() == ioRedirect.OUTPUT) {
                    outRedirection(O_TRUNC, ioRedirect);
                } else if (ioRedirect.getType() == ioRedirect.INPUT) {
                    inRedirection(ioRedirect);
                } else if (ioRedirect.getType() == ioRedirect.APPEND) {
                    outRedirection(O_APPEND, ioRedirect);
                }
            }
        }
        execCmd();


    } else {
        printf("Unknown command!\n");

    }

}


void SimpleCommand::pwd(){
    char cwd[1024];
    getcwd(cwd,sizeof(cwd));
    std::cout << cwd<< std::endl;

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
    pwd();
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

void SimpleCommand::outRedirection(int flag, IORedirect ioRedirect) {
    const char *file = ioRedirect.getNewFile().c_str();

    int fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
    if (fd != -1) {
        close(1);
        dup(3);
        close(3);
    }

}

void SimpleCommand::inRedirection(IORedirect ioRedirect) {
    const char *file = ioRedirect.getNewFile().c_str();

    int fd = open(file, O_RDONLY);
    if (fd != -1) {
        close(0);
        dup(3);
        close(3);
    }


}


