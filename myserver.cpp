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
    printf("Connect from:%s[%d]\n",inet_ntoa(sai_cli->sin_addr),ntohs(sai_cli->sin_port));
    MySocket * ms = new MySocket(sk_cli, &sa_cli);

    return ms;
}

vector<MySocket *> MyServer::selectaccept(){
    int rsize;
    struct timespec ts{0,250000000};
    struct sockaddr sa_cli;
    fd_set rfd;
    int sk_cli;
    int len;
    vector<MySocket *> res;

    FD_ZERO(&rfd);
    FD_SET(skfd, &rfd);

    
    rsize = pselect(FD_SETSIZE,&rfd, NULL, NULL, &ts,NULL);
    if(rsize==-1){
    
    }else if(rsize == 0){
    }else{
        for(int i=0; i<rsize; i++){
            sk_cli = accept(skfd, &sa_cli, (socklen_t *)&len);
            if(sk_cli==-1){
                cout<<"accept fail"<<endl;
                perr();
            }else{
                res.push_back(new MySocket(sk_cli, &sa_cli));
            }

        }
    }
    return res; 
}

MyServer::~MyServer(){
    close(skfd);
}
    
