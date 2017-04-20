#include "myserver.h"
//#include "httphandler.h"

string blank = "HTTP/1.1 200 OK\r\nContent-Length:0\r\nContent-Type:text/html\r\n\r\n";

MyServer::MyServer(int arg_port,char * arg_addr):port(arg_port),addr(arg_addr){
    skfd = socket(AF_INET, SOCK_STREAM, 0);
    if(skfd<0){
        cout<<"create error"<<endl;
        perr();
    }
    memset(&sa, '\0', sizeof(struct sockaddr));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = inet_addr(addr);

    int optval = 1;
    int state = -1;
    state = setsockopt(skfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if(state<0){
        cout<<"setsockopt fail"<<endl;
        perr();
    } 

    state = bind(skfd, (struct sockaddr *)&sa, sizeof(struct sockaddr));
    if(state<0){
        cout<<"bind error"<<endl;
        perr();
    }
    listen(skfd, SOMAXCONN);
}

MySocket * MyServer::myaccept(){
    int sk_cli;
    int len=sizeof(struct sockaddr);
    struct sockaddr sa_cli;
    struct sockaddr_in *sai_cli;

    sk_cli = accept(skfd, &sa_cli, (socklen_t *)&len);

    if(sk_cli==-1){
        cout<<"accept fail"<<endl;
        perr();
        return NULL;
    }

    sai_cli = (struct sockaddr_in *)&sa_cli;
    //printf("%x\n", sai_cli->sin_addr.s_addr);
    printf("Connect from:%s[%d]\n",inet_ntoa(sai_cli->sin_addr),ntohs(sai_cli->sin_port));

    MySocket * ms = new MySocket(sk_cli, &sa_cli);

    return ms;
}

MyServer::~MyServer(){
    close(skfd);
}
    




int main(int argc, char **argv){

    if(argc==3){
        MyServer s(atoi(argv[2]), argv[1]);
        MySocket* sfd;
        HttpHandler hh;
        string rbuff;
        while(1){
            sfd = s.myaccept();
            if(sfd && sfd>=0){
                int i=0;
                sfd->myread(rbuff);
                //cout<<rbuff<<endl;
                hh.handler(sfd,rbuff);
                rbuff.clear();
                delete sfd;
            }else{
                printf("---------------------->Error with sfd[%d]\n",sfd);
            }
        }
    }

    return 0;

}
