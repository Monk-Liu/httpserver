#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>


int main(){
    int sk,sk_cli;
    struct sockaddr_in sa, sa_cli;
    char rbuff[100],sbuff[100];

    sk = socket(AF_INET, SOCK_STREAM, 0);
    if(sk<0){
        return 0;
    }
    memset(&sa, '\0', sizeof(struct sockaddr_in));
    //bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(sk, (struct sockaddr *)&sa, sizeof(sa));
    listen(sk,0);

    while(1){
        int len;
        sk_cli = accept(sk,(struct sockaddr *)&sa_cli,(socklen_t *)&len);

        printf("recv from %s\n", inet_ntoa(sa_cli.sin_addr));
        sprintf(sbuff,"welcome %s:\n",inet_ntoa(sa_cli.sin_addr));
        send(sk_cli, sbuff, strlen(sbuff)+1,0);

        close(sk_cli);
    }
    return 0;
}
