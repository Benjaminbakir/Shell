#include <iostream>
#include <unistd.h>
#include <wait.h>
#include "Pipeline.h"
#include "SimpleCommand.h"

/**
 * Destructor.
 */
Pipeline::~Pipeline() {
    for (SimpleCommand *cmd : commands)
        delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {

    int counter = 0;

    int Pipe[2];

    for (SimpleCommand *cmd : commands) {
        counter++;
        if (commands.size() > 1) {
            if (counter == 1) {
                //Firts command that has to be execute
                pipe(Pipe);

                int cid = fork();

                if(cid ==0){
                    dup2(Pipe[1],1);
                    close(Pipe[1]);
                    close(Pipe[2]);
                    cmd->execute();
                    _exit(EXIT_SUCCESS);
                }
            }else if(counter!=commands.size()){
                //the middle section
                int cid = fork();
                if(cid==0){
                    dup2(Pipe[0],0);
                    close(Pipe[1]);
                    close(Pipe[0]);

                    pipe(Pipe);

                    dup2(Pipe[1],1);
                    close(Pipe[0]);
                    close(Pipe[1]);
                    cmd-> execute();
                    _exit(EXIT_SUCCESS);

                }

            }else{
                //The last command to execute
                int cid = fork();

                if(cid==0){
                    dup2(Pipe[0],0);
                    close(Pipe[1]);
                    close(Pipe[0]);
                    cmd->execute();
                    _exit(EXIT_SUCCESS);
                }
            }



        } else {//One command so execute it
            int cid = fork();
            if (cid == 0) {
                cmd->execute();
            }

        }
    }
}
