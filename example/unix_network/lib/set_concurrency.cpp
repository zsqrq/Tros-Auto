//
// Created by wz on 24-1-10.
//
#include	"common/unpipc.h"
#include <thread>
#include <threads.h>

int
set_concurrency(int level)
{
#ifdef	HAVE_THR_SETCONCURRENCY_PROTO
  int		thr_setconcurrency(int);

	return(thr_setconcurrency(level));
#else
  return(0);
#endif
}

void
Set_concurrency(int level)
{
  if (set_concurrency(level) != 0)
    err_sys("set_concurrency error");
}
