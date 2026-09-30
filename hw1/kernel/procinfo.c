#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "procinfo.h"

extern struct spinlock wait_lock;

uint64
sys_procinfo(void)
{
  uint64 addr;
  struct pinfo pi;
  struct proc *p = myproc();

  argaddr(0, &addr);
  if(addr == 0)
    return -1;

  acquire(&wait_lock);
  pi.ppid = p->parent ? p->parent->pid : 0;
  release(&wait_lock);

  pi.syscall_count =p->syscall_count;

  pi.page_usage =(p->sz+PGSIZE-1)/PGSIZE;
  //or (p->sz-1)/PGSIZE+1;

  if(copyout(p->pagetable, addr, (char *)&pi, sizeof(pi)) < 0)
    return -1;
  return 0;
}
