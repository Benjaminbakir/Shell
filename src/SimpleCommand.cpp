#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>
#include <wait.h>
#include "SimpleCommand.h"

void SimpleCommand::execute() {

    //wanneer het een cd command is wordt hij los uitgevoert anders voeren we het command of de redirection uit
    if (command == "cd") {
        cd();
    } else if (command != "") {
        if (redirects.empty()) {
            execCmd();
        } else {
           ioRedirections();
        }
        execCmd();
    } else {
        printf("Unknown command!\n");

    }

}
//code voor een cd command
void SimpleCommand::cd() {

    if (arguments.size() == 0) {
        chdir(getenv("HOME"));
    } else if (arguments.size() == 1) {
        if (arguments[0] == "~") {
            chdir(getenv("HOME"));
        }
        const char *c = arguments[0].c_str();

        chdir(c);
        exit(EXIT_SUCCESS);
    }
    waitpid(0,0,0);



}

//code voor het uitvoeren van een normaal command
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

//code voor het uivoeren van een redirection out
void SimpleCommand::outRedirection(int flag, IORedirect ioRedirect) {
    const char *file = ioRedirect.getNewFile().c_str();
    int fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
    if (fd != -1) {
        close(1);
        dup(3);
        close(3);
    }

}
//code voor het uitvoer van een redirection in
void SimpleCommand::inRedirection(IORedirect ioRedirect) {
    const char *file = ioRedirect.getNewFile().c_str();
    int fd = open(file, O_RDONLY);
    if (fd != -1) {
        close(0);
        dup(3);
        close(3);
    }
}

//code om te kijkne welk type redirection er moet worden uitgevoerd
void SimpleCommand::ioRedirections() {
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


