#include<sched.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>

#define SCHED_MYFIFO 7

 struct sched_attr {
   __u32 size;

   __u32 sched_policy;
   __u64  sched_flags;

   /* SCHED_NORMAL, SCHED_BATCH */
   __s32 sched_nice;

   /* SCHED_FIFO, SCHED_RR */
   __u32 sched_priority;

   /* SCHED_DEADLINE (nsec) */
   __u64 sched_runtime;
   __u64 sched_deadline;
   __u64 sched_period;
 };

static int sched_setattr(pid_t pid, const struct sched_attr* attr, unsigned int flags)
{
	return syscall(SYS_sched_setattr, pid, attr, flags) ;
}

int main()
{
	int result ;
	
	struct sched_attr attr ;
	
	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;
	
	attr.sched_policy = SCHED_MYFIFO;
    attr.sched_runtime = 10 * 1000 * 1000;
    attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;
	
	result = syscall(314,getpid(),&attr,0);//sched_setattr(getpid(),&attr,0) ;
	if(result == -1)
	{
		perror("Error calling sched_setattr") ;
	}
	
	while(1)
	{
		int i,j,k ;
		int sum = 0 ;
		
		for(i=0 ; i<1000 ; i++)
		{
			for(j=0 ; j<1000 ; j++)
			{
				for(k=0 ; k<1000 ; k++)
				{
					sum = sum + i - j + k ;
				}
			}
		}
		
		printf("%d\n",sum) ;//
		sum = 0 ;
	}
	
	return 0 ;
}