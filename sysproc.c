#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int
sys_setdeadline(void)
{
  int d;
  if(argint(0, &d) < 0)
    return -1;

  myproc()->deadline = d;
  return 0;
}
int
sys_getproc_exec_time(void)
{
    return myproc()->exec_time;
}
int
sys_getdeadline(void)
{
  return myproc()->deadline;
}
int
sys_getproc_missed_deadline(void)
{
  return myproc()->missed_deadline;
}




int sys_getallprocinfo(void)
{
    struct proc_info *buf;
    int i;

    if(argptr(0, (char**)&buf, sizeof(struct proc_info)*NPROC) < 0)
        return -1;

    acquire(&ptable.lock);
    for(i = 0; i < NPROC; i++){
        buf[i].pid = ptable.proc[i].pid;

        if(ptable.proc[i].state != UNUSED)
            safestrcpy(buf[i].name, ptable.proc[i].name, sizeof(buf[i].name));
        else
            buf[i].name[0] = '\0'; // empty string

        buf[i].deadline = ptable.proc[i].deadline;
        buf[i].exec_time = ptable.proc[i].exec_time;
        buf[i].missed_deadline = ptable.proc[i].missed_deadline;
    }
    release(&ptable.lock);

    return NPROC;
}

