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

#define DEBUG 

#ifdef  DEBUG
#define     DEBUG_MSG(x)    printf("%s\n", x)
#else
#define     DEBUG_MSG(x)
#endif

#define ERROR_MSG(x)  fprintf(stderr, "%s\n", (x))

//#define DEFAULT_HOST "smtp.uconn.edu"
//#define DEFAULT_PORT 25
#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 2525


//Email struct is a handy way to organize your email fields, 
//the fields are not dynamically sized so things will get truncated
#define     EMAIL_ADDRLEN   100
#define     EMAIL_MESGLEN   1000
typedef struct Email{
    char from[EMAIL_ADDRLEN];
    char to[EMAIL_ADDRLEN];
    char message[EMAIL_MESGLEN];
} Email;

//Payload struct just holds a buffer (you'll have to 
//malloc it before use and free it afterwards) and 
//the buffers size. For use with socket_read and get_server_response.
typedef struct Payload {
    char* buf;
    int   sz;
} Payload;

/* function prototypes */
int   socket_send(int sid, char* message);
int   socket_read(int sid, Payload *pp);
int   get_server_response(int sid, Payload *pp);
void  check_error(int status, int line_no);


/* This function reads a line from stdin.
 * It remove the ending newline.
 * A long line is broken into multiple lines.
 *
 * Returns the length of the line, or -1 for EOF.
 * */
int get_line(char *buf, int size)
{
    buf[0] = 0;

    char *p = fgets(buf, size, stdin);

    if (p == NULL)
        return -1;

    int len = strlen(buf);

    if (len > 0 && p[len-1] == '\n') {
        len --;
        p[len] = 0;
    }
    return len;
}

int main(int argc, char*argv[])
{
    /*First, connect to the server */
    int port;
    char* servername;
    servername = (argc > 1)? argv[1] : DEFAULT_HOST;
    port = (argc > 2)? atoi(argv[2]) : DEFAULT_PORT;
    struct hostent *server = gethostbyname(servername);

    if (server==NULL){
        perror("Error, no such host\n");
        exit(1);
    }

    //Connects to the server (either default or set by commmand line)
    struct sockaddr_in serv_addr;

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd<0) exit(-1);

    serv_addr.sin_port = htons(port);
    int status = connect( sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    check_error(status, __LINE__);
    printf("Connected to %s:%d successfully\n", servername, port);

    /* Get your machines fully qualified domain name, stored in fqdn variable*/
    struct addrinfo hints;
    struct addrinfo* info;
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    getaddrinfo(hostname ,"http", &hints, &info);
    char* fqdn = info[0].ai_canonname;
    printf("FQDN of local machine: %s\n", fqdn);

    //Now that the connection is made in sockfd 
    //(variable holding the sockets file descriptor), 
    //gather the information to send to the server, talk to the server to read it, and 
    //Solution goes here
    
    Email email;
    char line[EMAIL_MESGLEN];

    bzero((char*) &email.message, sizeof(email.message));
    printf("From:");
    if (get_line(email.from, sizeof(email.from)) <= 0) {
        ERROR_MSG("Did not get FROM address."); exit(-1);
    }

    printf("To:");
    if (get_line(email.to, sizeof(email.to)) <= 0) {
        ERROR_MSG("Did not get TO address."); exit(-1);
    }
    printf("Message(end with a line of a single '.':\n");

    // read messages line by line, 
    // with newline removed, add CRLF
    // the message ends with a line that has a single '.'
    int msg_len = 0;
    do {
        int len = get_line(line, EMAIL_MESGLEN);
        if (len < 0) {
            ERROR_MSG("Message must end with a line of '.'."); exit(-1);
        }

        if (msg_len + len + 3 >= EMAIL_MESGLEN) {
            ERROR_MSG("Message is too long."); exit(-1);
        }  
        strcpy(email.message + msg_len, line);
        msg_len += len;
        strcpy(email.message + msg_len, "\r\n");
        msg_len += 2;
        // DEBUG_MSG(line);
    } while (msg_len < 4 || line[0] != '.' || line[1] != 0);

    // Allocate 10 bytes to pr.buf for now.
    // You are going to free it.
    Payload pr;
    pr.buf = (char*) malloc(10);
    pr.sz = 10;

    #define CHECK_RETURN_CODE(x, code)  do {if ((x) != (code)) ERROR_MSG(pr.buf);} while (0)

    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 220);

    snprintf(line, EMAIL_MESGLEN, "HELO %s\r\n", fqdn);
    socket_send(sockfd, line);
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 250);
    //doing this to prevent compiler warnings/errors about truncated writing
    char email_from[75];
    strncpy(email_from, email.from, 75);
    snprintf(line, EMAIL_ADDRLEN, "MAIL From: %s\r\n", email_from);
    socket_send(sockfd, line);
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 250);

    char email_to[75];
    strncpy(email_to, email.to, 75);
    snprintf(line, EMAIL_ADDRLEN, "RCPT To: %s\r\n", email_to);
    socket_send(sockfd, line);
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 250);

    socket_send(sockfd, "DATA\r\n");
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 354);

    socket_send(sockfd, email.message);
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 250);

    // Now message is read. Everything is ready. 
    // Your turn to send it out.
    socket_send(sockfd, "QUIT\r\n");
    CHECK_RETURN_CODE(get_server_response(sockfd, &pr), 221);
    free(pr.buf);
    freeaddrinfo(info);
    return 0;
}

void check_error(int status, int line)
{
    if (status < 0){
        printf("socket error(%d)-%d: [%s]\n", getpid(), line, strerror(errno));
        exit(-1);
    }
}

/*  Socket_send() will just take a socket id and a message and 
 *  keep trying to send until the whole message has sent.
 *  The message is a string that ends with a NULL.
 *
 *  Returns the number of bytes sent.
 */
int socket_send(int sid, char* message)
{
    int status;
    int sent = 0;
    int rem = strlen(message);

    while(rem != 0){
        status = send(sid, message+sent, rem, 0);
        //check_error(status, __LINE__);
        sent+=status;
        rem-=status;
    }
    
    return sent;
}

/*
    Socket_read takes an initialized payload struct and will 
    resize (increase) the buffer as necessary to hold a line
    of response from the socket specified.
    Note that a line MUST end with CR and LF ('\r' then '\n').

    returns the length of the line received from the socket.

    you can terminate the program if read(), recv(), or realloc() fails.
*/
int  socket_read(int sid, Payload* p) 
{
    int ttl = 0;
    char c = 'a', pastc = 'a';

    do{
        if(p->sz <= ttl+3){
            p->buf = (char*)realloc(p->buf, ttl+50);
            p->sz = ttl+50;
        }
        pastc = c;
        int temp = recv(sid,&c,1,0);
        p->buf[ttl] = c;
        ttl += temp;
    }while(c != '\n' && pastc != '\r');
    
    
    p->buf[ttl] = '\0';
    DEBUG_MSG("Received:");
    DEBUG_MSG(p->buf);

    return ttl;
}


/* Call socket_read() to get a line of response.
 * Then, call sscanf() to find the code returned from the server. 
 *
 * You do not have to handle multiple lines from the server.
 *
 * return the code.
 */
int   get_server_response(int sid, Payload *pp)
{
    int  code = 0;
    int temp;
    
    socket_read(sid, pp);
    sscanf(pp->buf, "%d", &code);
    
    return code;
}
