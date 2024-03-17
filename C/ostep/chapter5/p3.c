#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    printf("hello (pid:%d) \n", (int) getpid());
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child process
        printf("child (pid:%d)\n", (int) getpid());
        char* myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p333.c");
        myargs[2] = NULL;

        execvp(myargs[0], myargs); // if successful, never returns
        printf("this shouldn't print out\n");
    }
    else
    {
        // int rc_wait = wait(NULL);
        int wstatus;
        waitpid(rc, &wstatus, 0);
        int return_value = WEXITSTATUS(wstatus);
        printf("parent of %d (exit code of child process:%d) (pid:%d) \n", rc, return_value, (int) getpid());
    }

    return 0;
}