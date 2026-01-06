#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;
    int status;


    pid1 = fork();

    if (pid1 == 0)
    {
        execl("./Lab-07x", "Lab-07x", "60", NULL);
        perror("exec failed");
        _exit(1);
    }


    pid2 = fork();

    if (pid2 == 0)
    {
        execl("./Lab-07x", "Lab-07x", "120", NULL);
        perror("exec failed");
        _exit(1);
    }

    printf("Waiting for child processes...\n");


    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    printf("Both child processes finished.\n");

    return 0;
}
