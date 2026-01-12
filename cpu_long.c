#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  setdeadline(2000);

  for(int i = 0; i < 1000000; i++)
    getpid();

  printf(1, "LONG exec=%d deadline=%d\n",
         getproc_exec_time(), getdeadline());

  if(getproc_missed_deadline())
    printf(1, "MISSED DEADLINE\n");
  else
    printf(1, "DEADLINE MET\n");

  exit();
}
