#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
int
sys_welcomeDone(void){
  return welcomeDone();
}
int 
sys_welcomeFunction(void){
  int n;
  argint(0, &n);
  uint address = (uint)n;
  return welcomeFunction(address);
}
int 
sys_setprio(void){
  int n;
  int status = argint(0, &n);
  if(status < 0){return -1;}
  return setprio(n);
}
int 
sys_getprio(void){
  return getprio();
}
int 
sys_getProcInfo(void){
  int pid,pinf;
  struct processInfo* procinf;
  int status = argint(0,&pid);
  if(status < 0){return -1;}
  status = argint(1,&pinf);
  if(status < 0){return -1;}
  procinf = (struct processInfo*)(pinf);
  return getProcInfo(pid,procinf);
}
int
sys_fork(void)
{
  return fork();
}
int 
sys_getMaxPid(void){
  return getMaxPid();
}
int
sys_getNumProc(void){
  return getNumProc();
}
void
sys_helloYou(void){
  char* name;
  argstr(0,&name);
  cprintf("%s",name);
  return;
}
void
sys_hello(void){
  cprintf("hello");
  return;
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
