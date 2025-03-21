//
// Created by wz on 24-1-17.
//
#include "common/unpipc.h"

int main(int argc, char** argv) {
  int		fd1, fd2, *ptr1, *ptr2;

  pid_t	childpid;
  struct stat	stat;

  if (argc != 2)
    err_quit("usage: test3 <name>");

  shm_unlink(argv[1]);
  fd1 = Shm_open(argv[1], O_RDWR | O_CREAT, FILE_MODE);
  Ftruncate(fd1, sizeof(int));
  fd2 = open("/dev/shm/motd", O_RDWR | O_CREAT | O_TRUNC, 0644);
  Fstat(fd2, &stat);

  if ((childpid = Fork()) == 0) {
    ptr2 = static_cast<int*>(mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd2, 0));
    ptr1 = static_cast<int*>(Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,MAP_SHARED, fd1, 0));
    printf("child: shm ptr = %p, motd ptr = %p\n", ptr1, ptr2);
    sleep(5);
    printf("shared memory integer = %d\n", *ptr1);
    exit(0);
  }
  ptr1 = (int*)Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  ptr2 = (int*)mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd2, 0);
  printf("parent: shm ptr = %p, motd ptr = %p\n", ptr1, ptr2);
  *ptr1 = 777;
  Waitpid(childpid, NULL, 0);

  exit(0);
}