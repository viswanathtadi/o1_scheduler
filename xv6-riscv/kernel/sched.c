//Linked list implementation

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"


struct sched_queue
{
	struct proc* q[2][40];
	struct proc* qlast[2][40];
	int sched_active;
};

struct sched_queue queue;

void 
sched_init()
{
	int i;
	for(i=0;i<40;i++)
	{
		queue.q[0][i]=queue.q[1][i]=queue.qlast[0][i]=queue.qlast[1][i]=0;
	}
	queue.sched_active = 0;
}

void 
sched_insert(struct proc* curp,int active)
{
	if(active!=0 && active!=1)panic("active value out of bounds");
	curp->next = 0;
	int p = curp->priority;
	int index;
	if(queue.sched_active != active)
	{
		index=0;
	}
	else if(queue.sched_active == active)
	{
		index=1;	
	}
	if(queue.q[index][p]==0)
	{
		queue.q[index][p]=curp;
		queue.qlast[index][p]=curp;
	}
	else
	{
		queue.qlast[index][p]->next=curp;
		queue.qlast[index][p]=curp;
	}
}

struct proc* 
sched_get()
{
	int i;
	struct proc* p;
	for(i=0;i<40;i++)
	{
		if(queue.q[queue.sched_active][i]!=0)
		{
			p = queue.q[queue.sched_active][i];
			queue.q[queue.sched_active][i] = queue.q[queue.sched_active][i]->next;
			if(p->next==0)
			{
				queue.qlast[queue.sched_active][i]=0;
			}
			return p;
		}
	}
	queue.sched_active = 1 - queue.sched_active;
	return sched_get();
}







