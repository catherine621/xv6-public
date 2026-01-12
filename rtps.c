#include "types.h"
#include "user.h"

int
main(void)
{
  struct proc_info buf[NPROC];
  int i, n;

  n = getallprocinfo(buf);

  printf(1, "PID NAME DEADLINE EXEC MISSED\n");

  for(i = 0; i < n; i++){
    if(buf[i].pid == 0)
      continue;

    printf(1, "%d %s %d %d %d\n",
           buf[i].pid,
           buf[i].name,
           buf[i].deadline,
           buf[i].exec_time,
           buf[i].missed_deadline);
  }

  exit();
}
