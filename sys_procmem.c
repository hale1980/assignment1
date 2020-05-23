#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

struct proc_segs {
	unsigned long mssv;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;
};
asmlinkage long sys_procmem(int pid, struct proc_segs * info){
	struct task_struct *task;
	int found = 0;

	for(task = &init_task; (task = next_task(task)) != &init_task; ){
		if(task->pid == pid) {
			found =1;
			break;
		}
	}
	if(found == 0) return -1;

	struct mm_struct * mm;
	mm = task->mm;
	info->mssv = 1812789;
	info->start_code = mm->start_code;
	info->end_code = mm->end_code;
	info->start_data = mm->start_data;
	info->end_data = mm->end_data;
	info->start_heap = mm->start_brk;
	info->end_heap = mm->brk;
	info->start_stack = mm->start_stack;

	return 0;
}
