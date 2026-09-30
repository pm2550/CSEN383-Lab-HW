#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "procinfo.h"

#define MAX_PROC 10

void print_sysinfo(void)
{
  int n_active_proc, n_syscalls, n_free_pages;
  n_active_proc = sysinfo(0);
  n_syscalls = sysinfo(1);
  n_free_pages = sysinfo(2);
  printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
         n_active_proc, n_syscalls, n_free_pages);
}

void check(char *name, int got, int want)
{
  printf("[check] %s: got %d, want %d -> %s\n",
         name, got, want, got == want ? "PASS" : "FAIL");
}

void test_errors(void)
{
  int a, b;
  a = sysinfo(1);
  b = sysinfo(1);
  check("sysinfo(1) excludes current call", b - a, 1);
  check("sysinfo(3)", sysinfo(3), -1);
  check("sysinfo(-1)", sysinfo(-1), -1);
  check("procinfo(NULL)", procinfo(0), -1);
  check("procinfo(unmapped addr)", procinfo((struct pinfo *)0x3000000000L), -1);
}

int main(int argc, char *argv[])
{
  int mem, n_proc, ret, proc_pid[MAX_PROC];
  int done[2];  // child -> parent: "I've finished printing"
  char c;
  if (argc < 3) {
    printf("Usage: %s [MEM] [N_PROC]\n", argv[0]);
    exit(-1);
  }
  mem = atoi(argv[1]);
  n_proc = atoi(argv[2]);
  if (n_proc > MAX_PROC) {
    printf("Cannot test with more than %d processes\n", MAX_PROC);
    exit(-1);
  }
  pipe(done);
  print_sysinfo();
  for (int i = 0; i < n_proc; i++) {
    sleep(1);
    ret = fork();
    if (ret == 0) {
      struct pinfo param;
      malloc(mem);
      for (int j = 0; j < 10; j++)//the last syscall is not counted
        procinfo(&param);
      printf("[procinfo %d] ppid: %d, syscalls: %d, page usage: %d\n",
             getpid(), param.ppid, param.syscall_count, param.page_usage);
      write(done[1], "x", 1);  // tell parent the output is complete
      while (1);
    }
    else {
      proc_pid[i] = ret;
      read(done[0], &c, 1);  // wait until this child has printed its line
      continue;
    }
  }
  sleep(1);
  print_sysinfo();
  for (int i = 0; i < n_proc; i++) kill(proc_pid[i]);
  test_errors();
  exit(0);
}
