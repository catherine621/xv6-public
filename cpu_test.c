#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    setdeadline(50);   // set any deadline, e.g., 50 ticks

    int i;
    for(i = 0; i < 1000000; i++) {  // busy loop to use CPU
        getpid(); // do nothing
    }

    printf(1, "CPU time used: %d\n", getproc_exec_time());
    exit();
}
