#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
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
        // child (new process)
        printf("child (pid:%d) \n", (int) getpid());
    }
    else
    {
        // parent
        // int rc_wait = wait(NULL);
        int wstatus;
        waitpid(rc, &wstatus, 0);
        int return_value = WEXITSTATUS(wstatus);
        printf("parent of %d (rc_wait:%d) (pid:%d) \n", rc, return_value, (int) getpid());
    }

    return 1;
}
