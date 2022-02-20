#define BUFFER_SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
void write_message(char * message, int fd) {
  int length = strlen(message);
  for(int i = 0; i < length;i++){
    write(fd, message+i, 1);
}
}

char* read_message(int fd) {
  // Read from fd until you hit a newline. 
  char* str = (char*)malloc(BUFFER_SIZE);
  int offset = 0;
  int check;
  int buffer = 20;
  do{
      check = read(fd, (str+offset), 1);
      offset+=1;
      if(offset == buffer-1){
          str = realloc(str, sizeof(buffer));
          buffer+=1;
      }
      if(str[offset-1] == '\n'){
          break;
      }
  } while(check != 0);
  str[offset] = '\0';
  return str;
}

void encrypt(char * message) {
  for(int i=0;i<strlen(message);i++) {
    if(message[i] == '\n') break;
        message[i] += 1;
  }
 
}
void decrypt(char * message) {
  for(int i=0;i<strlen(message);i++) {
    if(message[i] == '\n') break;
    message[i] -= 1;
  }
}



int main() {
  // Set up pipes
  int pTOc1[2], c1TOc2[2], c2TOp[2];
  // Create Pipes
  pipe(pTOc1);
  pipe(c1TOc2);
  pipe(c2TOp);

  pid_t pid1 = fork();
  if (pid1 == 0) {
    // Child 1
    char* msg;
    // TODO: Close Unneeded Pipes
    close(c2TOp[0]);
    close(c2TOp[1]);
    close(pTOc1[1]);
    close(c1TOc2[0]);
    msg = read_message(pTOc1[0]);
    printf("Child 1 is Encrypting!\n");
    encrypt(msg);
    write_message(msg,c1TOc2[1]);
    // TODO: Close Remaining Pipes
    close(pTOc1[0]);
    close(c1TOc2[1]);
    exit(0);
  } else {
    pid_t pid2 = fork();
    if (pid2 ==0) {
      // Child 2
      char* msg;
      // TODO: Close Unneeded Pipes
      close(pTOc1[0]);
      close(pTOc1[1]);
      close(c1TOc2[1]);
      close(c2TOp[0]);
      msg = read_message(c1TOc2[0]);
      printf("Child 2: %s", msg);
      write_message(msg, c2TOp[1]);
      // TODO: Close Remaining Pipes
      close(c1TOc2[0]);
      close(c2TOp[1]);
      exit(0);
    } else {
      // Parent
      char * msg = "This is a test.\n";
      //TODO: Close Unneeded Pipes
      close(c1TOc2[0]);
      close(c1TOc2[1]);
      close(pTOc1[0]);
      close(c2TOp[1]);
      printf("Parent: %s", msg);
      write_message(msg,pTOc1[1]);
      msg = read_message(c2TOp[0]);
      decrypt(msg);
      printf("Parent: %s", msg);
      // TODO: Close Remaining Pipes and free the msg
      close(pTOc1[1]);
      close(c2TOp[0]);
      free(msg);
      return 0;
    }

  }
}
