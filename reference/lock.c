#include "lock.h"

void AquireGlobalLock() {
  while(*_lock);
}

void ReleaseGlobalLock() {
  *_lock = 0;
}

int getProc() {
  AquireGlobalLock();
  int procnum = _proccounter;
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
    while (_join_n < proc_total);
    return 0;
  }
  return 1;
}
