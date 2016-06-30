#include "lock.h"

#include <stdio.h>

inline void AquireGlobalLock() {
  while(*_lock);
}

inline void ReleaseGlobalLock() {
  *_lock = 0;
}

int getProc() {
  AquireGlobalLock();
  int procnum = _proccounter;
  printf("Processor %d started\n", procnum);
  _proccounter++;
  ReleaseGlobalLock();
  return procnum;
}

int getTotalProcNumber() {
  return _proccounter;
}

int Join(int proc_num, int proc_total) {
  AquireGlobalLock();
  _join_n++;
  ReleaseGlobalLock();
  if (proc_num == 0) {
	printf("Process 0 waiting for others to join\n");
    while (_join_n < proc_total);
    return 0;
  }
  return 1;
}
