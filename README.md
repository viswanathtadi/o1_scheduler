# O(1) Scheduler for XV6 Operating System.

## Scheduler in Operating Systems
The scheduler is operating system software that decides which processes run when. A typical scheduler handles process priorities, allocation of resources, load balancing across processors.

## History of Linux schedulers

### O(n) Scheduler [Linux 2.4 - 2.6]
At every context switch, all the processes in the queue are scanned and the best one is picked.
It was discontinued because of scalability issues.

### O(1) Scheduler [Linux 2.6 - 2.6.22]
Constant time required to pick the next process to execute. Hence, it easily scales to a large number of processes.
It was discontinued because of complex heuristics used to distinguish between interactive and non-interactive processes.

### CFS Scheduler [Linux 2.6.23 - present]
At every context switch, the process with the least processor runtime is picked in O(log N) time.
It uses red-black trees to achieve this.

## XV6 Operating system
xv6 is a modern reimplementation of Sixth Edition Unix in ANSI C for multiprocessor x86 and RISC-V systems.

## XV6 native scheduler
XV6 uses a First In First Out scheduling policy. Hence, there is no support for prioritization and dynamic time slicing.

## O(1) Scheduler for XV6
The O(1) scheduler supports priority-based scheduling and implements dynamic behavior-based bonuses using certain heuristics.
It achieves this through a pair of identical multi-level queue data structures, the active queue, and passive queue.

Dynamic priorities range from 0 to 39. All new processes start with a priority of 20. A process stops running when its time slice is over(or through a voluntary system call). It is now placed into a passive queue after recomputing its dynamic priority based on its latest run.

The first process in the first non-empty queue within the active multi-queue is picked to run. Its time slice is calculated based on its dynamic priority and several heuristics.

The active and passive multi queues are swapped when the active multi-queue becomes empty.
