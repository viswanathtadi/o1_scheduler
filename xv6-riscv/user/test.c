#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int pid1, pid2, pid3;
	pid1 = fork();
	if(pid1 == 0){
		setpriority(35);
		int temp = fork();
		if(temp == 0){
			exit(0);
		}else{
			wait(0);
			printf("PID : %d, Dynamic Priority : %d\n",getpid(),getpriority());
			exit(0);
		}
	}else{
		pid2 = fork();
		if(pid2 == 0){
			setpriority(25);
			int temp = fork();
			if(temp == 0){
				exit(0);
			}else{
				wait(0);
				printf("PID : %d, Dynamic Priority : %d\n",getpid(),getpriority());
				exit(0);
			}
		}else{
			pid3 = fork();
			if(pid3 == 0){
				setpriority(15);
				int temp = fork();
				if(temp == 0){
					exit(0);
				}else{
					wait(0);
					printf("PID : %d, Dynamic Priority : %d\n",getpid(),getpriority());
					exit(0);
				}
			}
		}
	}
	exit(0);
}
