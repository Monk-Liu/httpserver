#ifndef MYSERVER_H
#define MYSERVER_H 1
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include "perror.h"
#include "mysocket.h"

using namespace std;



class MyServer{
    int skfd;
    struct sockaddr_in sa;
    const char * addr;
    const int port;

public:
    MyServer(int arg_port,char * arg_addr); 
    MySocket * myaccept();
    vector<MySocket *> selectaccept(); 
    ~MyServer();
};
#endif
