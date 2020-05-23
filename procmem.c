#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#include "procmem.h"

long procmem(pid_t pid, struct proc_segs * info){
	long sysvalue ;
	sysvalue = syscall(546, pid, info);

	return sysvalue;
}
