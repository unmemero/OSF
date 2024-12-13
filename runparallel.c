#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    /*CHeck nbum args*/
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num of jobs> <executable> [<arg1> ... <argn>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /*Check jobs*/
    char *endptr;
    errno = 0;
    long num_jobs = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || num_jobs <= 0) {
        fprintf(stderr, "Cannot convert \"%s\" to a positive integer\n", argv[1]);
        return EXIT_FAILURE;
    }

    /*ALlocate mem for pids*/
    pid_t *child_pids = calloc(num_jobs, sizeof(pid_t));
    if (child_pids == NULL) {
        fprintf(stderr, "Error: calloc failed\n");
        return EXIT_FAILURE;
    }

    /*Fork child*/
    for (long i = 0; i < num_jobs; ++i) {
        pid_t pid = fork();
        
        /*Fork failed*/
        if (pid < 0) {
            fprintf(stderr, "Error: fork failed: %s\n", strerror(errno));
            for (long j = 0; j < i; ++j) waitpid(child_pids[j], NULL, 0);
            free(child_pids);
            return 1;
        }

        if (pid == 0) {
            char job_number[32];
            snprintf(job_number, sizeof(job_number), "%ld", i);

            /*Get args*/
            char **exec_args = calloc(argc + 1, sizeof(char *));
            if (exec_args == NULL) {
                fprintf(stderr, "Error: calloc failed\n");
                exit(EXIT_FAILURE);
            }

            /*Get exec name and job num*/
            exec_args[0] = argv[2]; 
            exec_args[1] = job_number; 
            for (int j = 3; j < argc; ++j) exec_args[j - 1] = argv[j];

            execvp(argv[2], exec_args);

            /*execvp fails*/
            fprintf(stderr, "Error: execvp failed: %s\n", strerror(errno));
            free(exec_args);
            return 1;
        } else child_pids[i] = pid;
    }

    /*Wait for children*/
    int status;
    for (long i = 0; i < num_jobs; ++i) {
        if (waitpid(child_pids[i], &status, 0) == -1) fprintf(stderr, "Error: waitpid failed: %s\n", strerror(errno));
        else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) fprintf(stderr, "Child %ld exited with failure status\n", i);
    }

    free(child_pids);
    return EXIT_SUCCESS;
}
