#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int i = 0;
	while(i < 20){
		int pid = fork();
		if(pid==0){
			setpriority(i);
			int pid2 = fork();
			if(pid2 == 0){
				exit(0);
			}else{
				wait(0);
			}
			printf("PID : %d : Priority : %d\n",getpid(),getpriority());
			exit(0);
		}
		i +=1;
	}
	printf("Parent PID : %d\n",getpid());
	exit(0);
}
