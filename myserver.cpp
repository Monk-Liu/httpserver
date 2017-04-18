#include "myserver.h"
#include "httphandler.h"

string blank = "HTTP/1.1 200 OK\r\nContent-Length:62\r\nContent-Type:text/html\r\n\r\n";

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
    listen(skfd, 0);
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
    printf("%x\n", sai_cli->sin_addr.s_addr);
    printf("Connect from:%s[%d]\n",inet_ntoa(sai_cli->sin_addr),ntohs(sai_cli->sin_port));

    MySocket * ms = new MySocket(sk_cli, &sa_cli);

    return ms;
}

MyServer::~MyServer(){
    close(skfd);
}
    


MySocket::MySocket(int arg_skfd, struct sockaddr * arg_sa):skfd(arg_skfd){
    bcopy((char *)arg_sa, (char *)&sa, sizeof(struct sockaddr));
}

int MySocket::myread(string& rbuff){
    int res=0;
    int n=0;
    char buf[100];
    //res = getline(skfd, rbuff); getline 参数是一个fstream类, 然而skfd是int! 有什么通过int构建stream类的函数吗?
    do{
        n = read(skfd, buf, 100);
        res+=n;
        rbuff.append(buf);
    }while(n==100);

    return res;
}

int MySocket::mywrite(string& wbuff){
    int res=0;
    int n=0;
    char * buff= &wbuff[0u];
    do{
        n = write(skfd, buff+n, 100);
        res+=n;
    }while(n==100);

    return res;
}

MySocket::~MySocket(){
   close(skfd);
}


int main(int argc, char **argv){

    if(argc==3){
        MyServer s(atoi(argv[2]), argv[1]);
        MySocket* sfd;
        //HttpHandler hh;
        string rbuff;
        while(1){
            sfd = s.myaccept();
            if(sfd && sfd>=0){
                int i=0;
                cout<<sfd->myread(rbuff)<<endl;
                cout<<rbuff<<endl;
                //hh.handler(rbuff);
                rbuff.clear();
                sfd->mywrite(blank);
                delete sfd;
            }else{
                printf("---------------------->Error with sfd[%d]\n",sfd);
            }
        }
    }

    return 0;

}
