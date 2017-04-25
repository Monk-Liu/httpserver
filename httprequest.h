#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H 1
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "myutill.h"

using namespace std;

class HttpRequest{
    /*enum _method{
        GET,HEAD, POST,//in HTTP 1.0
        PUT, DELETE, CONNECT, OPTIONS, TRACE//HTTP 1.1
    }*/
    //_method method;
    //enum is not convenient

    string body;
    string method;
    string path;
    string version;
    map<string, string> headers;
    map<string, string> args;
    bool keep_alive;

    int parse_headers(string &);
    int parse_basic(string &);
    int parse_args(string &);
    int parse_path(string &);

public:
    bool ok;
    HttpRequest(string &);
    ~HttpRequest();
    const string & getmethod();
    const string & getpath();
    const string & getversion();
    const map<string, string> & getheaders();
    const map<string, string> & getargs();
    const bool is_alive();;
    const string & getbody();
};
#endif
