#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
void myls_bad_sys(const char *dir) {
  char cmd[1024];
  snprintf(cmd,sizeof(cmd),"/bin/ls '%s'",dir);
  system(cmd);
}

void myls(const char *dir) {
  DIR *dir = opendir(dirname);
  if (dir == NULL){
    perror(NULL);
    exit(1);
  }
  for (;;){
  struct dirent *entry = readdir(dir);
    if (entry == NULL) break;

    printf("%s\n",entry->d_name);
}
  if (closedir(dir) !=0){
    perror(NULL);
    exit(1);
  }
  printf("opened dir %s\n", dirname);
  // char buf[1024];
  // snprinf(sizeof(buf),buf,"/bin/ls '%s'",dir);
  // system(cmd);
  int pid = fork();
  if (pid == 0) {
    execl("/bin/ls","ls","--",dir,0);
    exit(1);
  } else {
    waitpid(pid,0,0);
  }
}

int main(int argc, char *argv[])
{
  if (argc == 1) {
    myls(".");
  } else {
    for (int i=1; i<argc; ++i) {
      myls(argv[i]);
    }
  }

  return 0;
}
