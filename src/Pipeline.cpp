#include <iostream>
#include <unistd.h>
#include "Pipeline.h"
#include "SimpleCommand.h"

/**
 * Destructor.
 */
Pipeline::~Pipeline() {
	for( SimpleCommand *cmd : commands )
		delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {
	std::cout << "FIXME: You should change Pipeline::execute()" << std::endl;



	for( SimpleCommand *cmd : commands ) {
		// FIXME: Probably need to set up some pipe here?
        if(commands.size()==1){
            cmd->execute();
            return;
        }
        //		int p[2];
//		pipe(p);
//		int cid = fork();
//		if(cid = 0){
//			dup2(p[0], 0);
//			close(p[0]);
//			close(p[1]);
//			cmd->execute();
//		}else{
//			dup2(p[1],1);
//			close(p[0]);
//			close(p[1]);
//			cmd->execute();
//		}


		cmd->execute();
	}
}