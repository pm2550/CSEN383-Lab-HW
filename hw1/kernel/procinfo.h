#ifndef _PROCINFO_H
#define _PROCINFO_H

struct pinfo {
  int ppid;
  int syscall_count;
  int page_usage;
};


#endif // _PROCINFO_H