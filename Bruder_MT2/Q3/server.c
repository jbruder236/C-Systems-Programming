#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <dirent.h>

void checkError(int status)
{
   if (status < 0) {
      printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
      exit(-1);
   }
}

char* readResponse(int fd) {
   int sz = 8;
   char* buf = malloc(sz);
   int ttl = 0,at = 0;
   int recvd;
   do {
      recvd = read(fd,buf+at,1);
      ttl += recvd;
      at  += recvd;
      if (recvd > 0 && ttl == sz) {
         buf = realloc(buf,sz*2);
         sz *= 2;
      }
      buf[ttl] = 0;
   } while (buf[ttl-1] != '\n' && recvd > 0);
   return buf;
}

int main(int argc,char* argv[]) 
{
   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);

   // Make the **server-side** socket non-blocking
   int flags = fcntl(sid, F_GETFL, 0);
   checkError(flags);
   flags = flags | O_NONBLOCK;
   int status = fcntl(sid, F_SETFL, flags);
   checkError(status);
   int enable = 1;
   status = setsockopt(sid, SOL_SOCKET,SO_REUSEADDR, &enable, sizeof(int));
   checkError(status);
  
   // setup our address -- will listen on 8025 --
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port   = htons(8075);
   addr.sin_addr.s_addr = INADDR_ANY;
   //pairs the newly created socket with the requested address.
   status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
   checkError(status);
   // listen on that socket for "Let's talk" message. No more than 10 pending at once
   status = listen(sid,10);
   checkError(status);
   
   int chatArr[100];
   
   while(1){
       struct sockaddr_in client;
       socklen_t clientSize = (socklen_t) sizeof(struct sockaddr_in);
       int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
       checkError(chatSocket);
       printf("We accepted a socket: %d\n",chatSocket);
       chatArr chatSocket
       
       fd_set read;
       int done = 0; //flag for exit command
       
       do{
           FD_ZERO(&read);
           FD_SET(chatSocket, &read); //a child
           FD_SET(sid, &read);
           int nbReady = select(sid+1, &read, NULL, NULL, NULL);
           
           
       }while(done != 1);
   }
   
   return 0;
}
