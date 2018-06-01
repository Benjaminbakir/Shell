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
                //Eerste command dat word uitgevoerd(begin van de pijp)
                pipe(Pipe);

                int cid = fork();

                if(cid ==0){
                    dup2(Pipe[1],1);
                    close(Pipe[1]);
                    close(Pipe[2]);
                    cmd->execute();
                    _exit(EXIT_SUCCESS);
                }

                waitpid(0,0,0);
            }else if(counter!=commands.size()){
                //De commands in het midden
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
                waitpid(0,0,0);

            }else{
                //Laatste command van de pijp
                int cid = fork();

                if(cid==0){
                    dup2(Pipe[0],0);
                    close(Pipe[1]);
                    close(Pipe[0]);
                    cmd->execute();
                    _exit(EXIT_SUCCESS);
                }

                waitpid(0,0,0);
            }



        } else {//er is maar een command dus wordt deze uitgevoerd
            int cid = fork();
            if (cid == 0) {
                cmd->execute();
            }

            waitpid(0,0,0);

        }

        
    }
}
