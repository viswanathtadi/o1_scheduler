#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void adjacent_swap(int *a, int k) {
	int temp;
	temp = a[k];
	a[k] = a[k+1];
	a[k+1] = temp;
}
