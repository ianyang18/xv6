#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    uint time; 
    if(argc < 2) {
        fprintf(2, "Usage: sleep time\n");
        exit(1);
    }

    time = atoi(argv[1]);
    sleep(time);
    exit(0);
}

