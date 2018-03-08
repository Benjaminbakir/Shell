#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "SimpleCommand.h"

void SimpleCommand::execute() {
    //std::cout << "FIXME: You should change SimpleCommand::execute()" << std::endl;
    // FIXME: Your code here...

    int cid = fork();
    if (cid == 0) {

        if (command == "cd") {
            cd();
        } else if (command == "pwd") {
            pwd();
        } else if (command == "ls") {
            ls();
        } else if (command == "cat") {
            cat();
        }else{
           printf("Unknown command!\n");

        }
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

void SimpleCommand::cat(){
    if(arguments.size()==0){
        char *args[]= {"cat",NULL};
    }
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

void IORedirect:: execute(){
    if(type==OUTPUT){
        std::cout << "Output"<< std::endl;

    }else if(type==APPEND){

    }else if(type==INPUT){


    }

}
