#ifndef HTTPHANDLER_H 
#define HTTPHANDLER_H 1
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "mysocket.h"
#include "httpresponse.h"
#include "httprequest.h"
#include "app.h"
#include "mythreadpool/mytask.h"

using namespace std;

class HttpHandler:public MyTask{
    MySocket * skfd;
    string reqstr;

public:
    HttpHandler(MySocket * skfd,string  str);

    void run();
    ~HttpHandler();
};
#endif
