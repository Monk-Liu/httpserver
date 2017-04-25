#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H 1
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "mysocket.h"
#include "myutill.h"

using namespace std;

class HttpResponse{
    int datalen;
    map<string, string> headers;
    string version;
    int status;
    string reason;
    bool headflag; //写data之前数据有没有写?
    MySocket* skfd;
    static map<string, string> mime_init();

    
public:
    static map<string,string> MIME_TYPE;
    int addHeader(string , string );
    int setHeader(string , string );
    int setStatus(int);
    int setVersion(string);
    int setDataLen(long);
    int writeData(char*,int);
    int writeData(string &);
    int writeHeader();
    int finish();

    HttpResponse(MySocket * arg_skfd);
    ~HttpResponse();
};

#endif
