#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
	int p[2][2];
	pipe(p[0]);
	for(int i = 2; i <= 35; ++i) {
		write(p[0][1], &i, sizeof(int));
	}
	close(p[0][1]);
	int idx = 0, sieve, num;
	while(fork() == 0) {
		if(read(p[idx][0], &sieve, sizeof(int))) {
			fprintf(1, "prime %d\n", sieve);
			pipe(p[1 ^ idx]);
			while(read(p[idx][0], &num, sizeof(int))) {
				if(num % sieve != 0) {
					write(p[1 ^ idx][1], &num, sizeof(int));
				}
			}
			close(p[1 ^ idx][1]);
			idx ^= 1;
		} else {
			exit(0);
		}
	}
	wait(0);
	exit(0);
}

