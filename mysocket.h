#ifndef MYSOCKET_H
#define MYSOCKET_H 1
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

class MySocket{
    struct sockaddr sa;
    const int skfd;
    char * buffer;
    const int  BUFFSIZE;

public:
    MySocket(int arg_skfd, struct sockaddr * arg_sa);
    MySocket(int arg_skfd);
    int myread(string& rbuff);
    int mywrite(char *wbuff, int len);
    int mywrite(string& wbuff);
    ~MySocket();
};

#endif
