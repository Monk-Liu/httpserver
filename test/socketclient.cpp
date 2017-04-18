#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

int main(){
    int sk,cfd;
    struct sockaddr_in sa;
    char rbuff[100];
    struct hostent * server;

    sk = socket(AF_INET, SOCK_STREAM, 0);
    memset(&sa,'\0', sizeof(struct sockaddr_in));

    sa.sin_family = AF_INET;
    sa.sin_port =htons(8080);

    server = gethostbyname("127.0.0.1");
//    sa.sin_addr.s_addr = server->h_addr;
    bcopy((char *)server->h_addr, (char *)&sa.sin_addr.s_addr,server->h_length);

    printf("connect start\n");
    cfd = connect(sk,(struct sockaddr *)&sa, sizeof(struct sockaddr));
    printf("connect finished \n");
    if(cfd==0){
        sleep(1);
        recv(sk, rbuff, 100,0);
        printf("%s\n",rbuff); 
    }else{
        if(errno==EADDRNOTAVAIL){
            printf("EADDRNOTAVAIL");
        }else if(errno==EAFNOSUPPORT){
            printf("EAFNOSUPPORT");
        }else if(errno==EALREADY){
            printf("EALREADY");
        }else if(errno==EBADF){
            printf("EBADF");
        }else if(errno==ECONNREFUSED){
            printf("ECONNREFUSED");
        }else if(errno==EINPROGRESS){
            printf("EINPROGRESS");
        }else if(errno==ETIMEDOUT){
            printf("TIMEOUT");
        }else{
            printf("?????");
        }
    }
    printf("end\n");

    close(sk);
    return 0;
}
