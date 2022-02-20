#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <netdb.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <unistd.h>
#include    <netinet/in.h>
#include    <errno.h>
#include    <assert.h>

int main(int argc,char* argv[])
{
   char* buf = argv[1];
   
   int dfTOgrep[2];
   pipe(dfTOgrep);
   
   pid_t child = fork();
   
   if(child == 0){
       //child
       //input from pipe and run grep
       close(0);
       dup(dfTOgrep[0]);
       close(dfTOgrep[1]);
       close(dfTOgrep[0]);
       execl("/bin/grep", "grep", buf, NULL);
   }
   else{
       //parent
       //run df and output to pipe
       close(1);
       dup(dfTOgrep[1]);
       close(dfTOgrep[0]);
       close(dfTOgrep[1]);
       execl("/bin/df", "df", "-h", NULL);
   }
}


