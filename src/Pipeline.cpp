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

    for (SimpleCommand *cmd : commands) {
        // FIXME: Probably need to set up some pipe here?
        counter++;


        if (commands.size() > 1) {
            if (counter == 1) {
              int p[2];
              pipe(p);
              int cid = fork();
              if(cid==0){
                  close(1);
                  dup(p[1]);
                  close(p[0]);
                  close(p[1]);
              }else{

              }


            } else if (counter != commands.size()) {




            } else {




            }

        } else {
            int cid = fork();
            if(cid==0){
                cmd->execute();
            }

        }
    }
}