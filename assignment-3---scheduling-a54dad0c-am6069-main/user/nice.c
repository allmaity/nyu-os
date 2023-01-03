#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  int priority, pid;
  if(argc != 3){
    printf(2,"Usage: incomplete parameters, needs nice pid priority\n");
    exit();
  }
  pid = atoi(argv[1]);
  priority = atoi(argv[2]);
  // printf(1,"%d",priority);
  if (priority < 1 || priority > 20){
    printf(2,"Priority range must be between: 1-20\n");
    exit();
  }
  nice(pid, priority);
  exit();
}  