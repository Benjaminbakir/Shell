#include <iostream>
#include <unistd.h>
#include "Sequence.h"
#include "Pipeline.h"

/**
 * Destructor.
 */
Sequence::~Sequence() {
	for( Pipeline *p : pipelines )
		delete p;
}

/**
 * Executes a sequence, i.e. runs all pipelines and - depending if the ampersand
 * was used - waits for execution to be finished or not.
 */
void Sequence::execute() {


	for( Pipeline *p : pipelines ) {
		if(p->isAsync()){//we check if the pipe is Async
		    int cid = fork();
		    if(cid==0){
		        p->execute();
		    }
		}else{
            p->execute();
        }
	}
}
