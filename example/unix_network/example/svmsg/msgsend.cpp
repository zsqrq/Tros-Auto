//
// Created by wz on 24-1-9.
//
#include "common/unpipcmsg.h"

int main(int argc, char** argv) {
  int mqid;
  size_t len;
  long type;
  struct msgbuf *ptr;
  int oflag = 0666 | IPC_CREAT;
  if (argc != 4) {
    err_quit("usage: msgsnd <pathname> <#bytes> <type>");
  }
  len = atoi(argv[2]);
  type = atoi(argv[3]);

  mqid = Msgget(Ftok(argv[1], 0), oflag);

  ptr = static_cast<struct msgbuf*>(Calloc(sizeof(long) + len, sizeof(char)));
  ptr->mtype = type;

  Msgsnd(mqid, ptr, len, 0);

  exit(0);
}