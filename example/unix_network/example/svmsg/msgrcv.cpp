//
// Created by wz on 24-1-9.
//
#include "common/unpipcmsg.h"

#define	MAXMSG	(8192 + sizeof(long))

int
main(int argc, char **argv)
{
  int		c, flag, mqid;
  long	type;
  ssize_t	n;
  struct msgbuf	*buff;

  type = flag = 0;
  while ( (c = Getopt(argc, argv, "nt:")) != -1) {
    switch (c) {
      case 'n':
        flag |= IPC_NOWAIT;
        break;

      case 't':
        type = atol(optarg);
        break;
    }
  }
  if (optind != argc - 1)
    err_quit("usage: msgrcv [ -n ] [ -t type ] <pathname>");

  mqid = Msgget(Ftok(argv[optind], 0), IPC_CREAT | 0666);

  buff = static_cast<struct msgbuf*>(Malloc(MAXMSG));

  n = Msgrcv(mqid, buff, MAXMSG, type, flag);
  printf("read %d bytes, type = %ld\n", n, buff->mtype);

  exit(0);
}