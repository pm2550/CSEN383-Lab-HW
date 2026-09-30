#ifndef SYSINFO_H
#define SYSINFO_H

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"

uint64 sys_sysinfo(void);

#endif