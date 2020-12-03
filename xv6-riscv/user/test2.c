#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int i;
	for(i=0;i<10;i++)
	{
		int pid = fork();
		if(pid==0)
		{
			int pid1 = fork();
			if(pid1==0)
			{
				int j;
				for(j=0;j<100000*i;j++)
				{
					int n = 0;
					n++;
				}
				exit(0);
			}
			else
			{
				wait(0);
				printf("dynamic priority : %d\n",getpriority());
				exit(0);
			}
		}
		else
		{
			wait(0);
		}
	}
	exit(0);
}
