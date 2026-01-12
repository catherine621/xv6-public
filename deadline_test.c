#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  setdeadline(100);
  printf(1, "Deadline set to 100\n");
  exit();
}
