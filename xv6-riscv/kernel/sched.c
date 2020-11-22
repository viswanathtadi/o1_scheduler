#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

//Linked list implementation

struct sched_queue
{
	struct proc* q[2][40];
	struct proc* qlast[2][40];
	int sched_active;
	struct spinlock lock[2][40];
	struct spinlock lock_active;
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
	int bonus = 4;
	if(!(curp->total_sleeptime==0 && curp->total_runtime==0)){
		bonus = ((curp->total_sleeptime*10)/(curp->total_sleeptime+curp->total_runtime));
	}
	int dprio = curp->priority - bonus + 4;
	if(dprio <= 0) dprio = 0;
	if(dprio >= 39) dprio = 39;
	curp->dynamic_priority = dprio;
	int p = curp->dynamic_priority;
	int index;
	
	acquire(&queue.lock_active);
	if(active == 1)
	{
		index = queue.sched_active;
	}
	else if (active == 0)
	{
		index = 1 - curp->last_queue;
	}
	release(&queue.lock_active);
	
	//printf("PID : %d , Queue : %d\n",curp->pid,p);
	
	acquire(&queue.lock[index][p]);
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
	release(&queue.lock[index][p]);
}

struct proc* 
sched_get()
{
	int i;
	struct proc* p;
	sched_L:
	acquire(&queue.lock_active);
	for(i=0;i<40;i++)
	{	
		acquire(&queue.lock[queue.sched_active][i]);
		if(queue.q[queue.sched_active][i]!=0)
		{
			p = queue.q[queue.sched_active][i];
			p->last_queue = queue.sched_active;
			queue.q[queue.sched_active][i] = queue.q[queue.sched_active][i]->next;
			if(p->next==0)
			{
				queue.qlast[queue.sched_active][i]=0;
			}
			release(&queue.lock[queue.sched_active][i]);
			release(&queue.lock_active);
			return p;
		}
		release(&queue.lock[queue.sched_active][i]);
	}
	queue.sched_active = 1 - queue.sched_active;
	
	for(i=0;i<40;i++)
	{	
		acquire(&queue.lock[queue.sched_active][i]);
		if(queue.q[queue.sched_active][i]!=0)
		{
			p = queue.q[queue.sched_active][i];
			p->last_queue = queue.sched_active;
			queue.q[queue.sched_active][i] = queue.q[queue.sched_active][i]->next;
			if(p->next==0)
			{
				queue.qlast[queue.sched_active][i]=0;
			}
			release(&queue.lock[queue.sched_active][i]);
			release(&queue.lock_active);
			return p;
		}
		release(&queue.lock[queue.sched_active][i]);
	}
	
	release(&queue.lock_active);
	goto sched_L;
}



