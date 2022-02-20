#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>
#include "analyze.h"

void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

char* readResponse(int sid)
{
   size_t sz = 8;
   char* buf = malloc(sizeof(char)* sz);
   int done = 0,received = 0;  
   while (!done) {
      int nbb = read(sid,buf + received,sz - received);
      if (nbb > 0)
         received += nbb;
      else if (nbb == 0)
         done = 1;
      if (received == sz) {
         buf = realloc(buf,sz * 2);
         sz  *= 2;
      }
   }
   if (received == sz)
      buf = realloc(buf,sz + 1);
   buf[received] = 0;
   return buf;
}

int main(int argc,char* argv[])
{
   // Create a socket
   if (argc < 2) {
      printf("Usage is: wgettext <url>\n");
      return 1;
   }
   char host[512];
   int  port = 80;
   char url[512];
   analyzeURL(argv[1],host,&port,url);
   printf("[%s] [%d] [%s]\n",host,port,url);
   fflush(stdout);

   // TODO
   // Feel free to start from the code in wgethtml.c
      int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   struct hostent *server = gethostbyname(host);
   srv.sin_family = AF_INET;
   srv.sin_port   = htons(port);
   memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);
   
   char msg[100] = "GET /";
   strcat(msg, url);
   
   strcat(msg, "\n");
   
   status = send(sid,msg,strlen(msg)+1,0);
   
   /////////////////////////////////////////////////////////////
   int html2text[2];
   pipe(html2text);
   
   pid_t child = fork();
   
   if(child == 0){
       //child
       //set pipe input as stdin and run html2text
       close(0);
       dup(html2text[0]);
       close(html2text[1]);
       close(html2text[0]);
       execl("/usr/bin/html2text", "html2text", NULL);
   }
   else{
       //parent
       //readresponse into pipe output
       close(1);
       dup(html2text[1]);
       close(html2text[0]);
       close(html2text[1]);
       printf("%s", readResponse(sid));
   }
   
   
   return 0;
}

