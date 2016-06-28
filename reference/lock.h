#ifndef __LOCK_H__
#define __LOCK_H__

// ---------------------------------------------------------------------------//
// Lock Peripheral

#define LOCK_ADDR			0x7400000

static volatile int *_lock = (int *)LOCK_ADDR;
static volatile int _proccounter = 0;
static volatile int _join_n = 0;

void AquireGlobalLock();

void ReleaseGlobalLock();

int getProc();

int getTotalProcNumber();

int Join(int proc_num, int proc_total);

#endif
