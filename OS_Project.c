#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/mutex.h>

int nResources = 3;
int nProcesses = 5;
int resources[3] = {3, 3, 2};
int allocated[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
int maxRequired[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
int need[5][3];
int safeSeq[3];
int nProcessRan = 0;


struct mutex lock_resources;
struct task_struct *processes[5];
void processCode(void* );
int getSafeSeq(void);

asmlinkage long bankers_algo(void) {
	int i, j;
	printk("Number of processes are %d.", nProcesses);
	printk("\nNumber of resources are %d.", nProcesses);
	printk("\nThe allocation matrix is:\n");
	 
	for( i=0; i<nProcesses; i++) {
		for( j=0; j<nResources; j++){
			printk("%d ", allocated[i][j]);
		}
		printk("\n");
	}
	// maximum required resources by each process
	printk("\nThe maximum resource matrix is:\n");
	for( i=0; i<nProcesses; i++) {
		for( j=0; j<nResources; j++){
			printk("%d ", maxRequired[i][j]);
		}
		printk("\n");
	}
	printk("\n");
	printk("The instances of currently available resources are:\n");
	for(i=0; i<nResources; i++){
		printk("R%d: %d\n", i+1, resources[i]);
	}
	// calculating the need matrix
	for( i=0; i<nProcesses; i++)
		for( j=0; j<nResources; j++)
	 		need[i][j] = maxRequired[i][j] - allocated[i][j];
	// getting the safe sequence of process execution
	for( i=0; i<nProcesses; i++) 
		safeSeq[i] = -1;
	if(!getSafeSeq()) {
		printk("\nUnsafe State! The processes leads the system to aunsafe state.\n\n");
	return -1;
	}
	printk("\n\nSafe Sequence Found : ");
	for( i=0; i<nProcesses; i++) {
		printk("%-3d", safeSeq[i]+1);
	}
	printk("\nExecuting Processes...\n\n");
	ssleep(1);
	//execute threads simultaneoulsy
	int processNumber[nProcesses];
	for( i=0; i<nProcesses; i++) processNumber[i] = i;
	for( i=0; i<nProcesses; i++)
		processes[i] = kthread_create(&processCode, (void *)(&processNumber[i]), "process");
	for( i=0; i<nProcesses; i++)
		wake_up_process(processes[i]);
	printk("\nAll Processes Finished\n");
}

int getSafeSeq(void) {
	 int tempRes[nResources];
	 int i, j;
	 for( i=0; i<nResources; i++) tempRes[i] = resources[i];
	 int finished[nProcesses];
	 for( i=0; i<nProcesses; i++) finished[i] = 0;
	 int nfinished=0;
	 while(nfinished < nProcesses) {
		 int safe = 0;
		 for( i=0; i<nProcesses; i++) {
			 if(!finished[i]) {
				 int possible = 1;
				 for(j=0; j<nResources; j++)
				 if(need[i][j] > tempRes[j]) {
					 possible = 0;
					 break;
				 }
				 if(possible) {
					 for( j=0; j<nResources; j++)
					 tempRes[j] += allocated[i][j];
					 safeSeq[nfinished] = i;
					 finished[i] = 1;
					 ++nfinished;
					 safe = 1;
				 }
			 }
		 }
		 if(!safe) {
			 int k;
			 for( k=0; k<nProcesses; k++) safeSeq[k] = -1;
			 return 0; // no safe sequence found
		 }
	}
	 return 1; // safe sequence found
}

void processCode(void *arg) {
	 int i;
	 int p = *((int *) arg);
	// lock
	 mutex_lock_interruptible(&lock_resources);
	// process
	 printk("\n--> Process %d", p+1);
	 printk("\n\tAllocated : ");
	 for( i=0; i<nResources; i++)
		 printk("%3d", allocated[p][i]);
	 printk("\n\tNeeded : ");
	 for( i=0; i<nResources; i++)
	 	printk("%3d", need[p][i]);
	 printk("\n\tAvailable : ");
	 for( i=0; i<nResources; i++)
	 	printk("%3d", resources[i]);
	 printk("\n"); ssleep(1);
	 printk("\tResource Allocated!");
	 printk("\n"); ssleep(1);
	 printk("\tProcess Code Running...");
	 printk("\n"); ssleep(3);
	 printk("\tProcess Code Completed...");
	 printk("\n"); ssleep(1);
	 printk("\tProcess Releasing Resource...");
	 printk("\n"); ssleep(1);
	 printk("\tResource Released!");
	for( i=0; i<nResources; i++)
	 	resources[i] += allocated[p][i];
	 printk("\n\tNow Available : ");
	 for( i=0; i<nResources; i++)
	 	printk("%3d", resources[i]);
	 printk("\n\n");
	 ssleep(1);
	nProcessRan++;
	mutex_unlock(&lock_resources);
}
