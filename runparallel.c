#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[]){
	if(argc < 3){
		fprintf(stderr, "Usage: %s <num of jobs> <executables>\n", argv[0]);
	}	

	int num_jobs;
	if((num_jobs = atoi(argv[1])) <= 0){
		fprintf(stderr, "Cannot convert \"%s\" to a positibe integer\n", argv[1]);
		exit(1);
	}

	pid_t pid;
	
}
