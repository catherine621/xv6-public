#ifndef USER_H
#define USER_H

#include "param.h"  // optional, if you want NPROC from xv6

#ifndef NPROC
#define NPROC 64   // fallback if param.h is not included
#endif

struct stat;
struct rtcdate;
struct proc_info {
    int pid;
    char name[16];
    int deadline;
    int exec_time;
    int missed_deadline;
};
// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int get_exec_time(void);
// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int setdeadline(int);
int getproc_exec_time(void);
int getdeadline(void);
int getproc_missed_deadline(void);
int getallprocinfo(struct proc_info *buf);
#endif  // USER_H