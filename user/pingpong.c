#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char buf[1];
    int fds[2];
    int n, pid;
    
    pipe(fds);
    
    pid = fork();
    if(pid == 0) {
        for(;;) {
            n = read(fds[0], buf, sizeof(buf));
            if(n > 0)
                break;
        }
        if(n == 1) {
            fprintf(1, "%d: received ping\n", getpid()); 
            write(fds[1], buf, sizeof(buf));
        }
        close(fds[0]);
        close(fds[1]);
        exit(0);
    } else {
        write(fds[1], buf, sizeof(buf));
        close(fds[1]);
        wait(0); 
        read(fds[0], buf, sizeof(buf));
        fprintf(1, "%d: received pong\n", getpid());
        close(fds[0]);
        exit(0);
    }
}
