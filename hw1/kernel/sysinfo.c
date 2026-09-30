#include "sysinfo.h"
extern struct proc proc[NPROC];

uint64
sys_sysinfo(void)
{
  int param;
  argint(0,&param);
  if(param == 0) {
    uint64 count = 0;
    struct proc *p;
    for(p = proc; p < &proc[NPROC]; p++) {
        acquire(&p->lock);
        if(p->state != UNUSED) {
          count++;
        }
        release(&p->lock);
    }
    return count;
  }else if(param == 1) {    
    return getnsyscalls();
  }
  else if(param == 2) {
    return freemem();
  }
  return -1;
}