#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
printf("%d\n",getpriority());
	setpriority(10);
	printf("%d\n",getpriority());
	exit(0);
}
