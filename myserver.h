#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include "perror.h"

using namespace std;


class MySocket{
    struct sockaddr sa;
    const int skfd;

public:
    MySocket(int arg_skfd, struct sockaddr * arg_sa);
    int myread(string& rbuff);
    int mywrite(string& wbuff);
    ~MySocket();
};

class MyServer{
    int skfd;
    struct sockaddr_in sa;
    const char * addr;
    const int port;

public:
    MyServer(int arg_port,char * arg_addr); 
    MySocket * myaccept();
    ~MyServer();
};
