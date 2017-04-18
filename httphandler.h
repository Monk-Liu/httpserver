#include <string>
#include <vector>
#include <map>

class HttpHandler{

public:
    handler(string & str);

    HttpHandler();
    ~HttpHandler();
};


classs HttpRequest{
    enum _method{
        GET,HEAD, POST,//in HTTP 1.0
        PUT, DELETE, CONNECT, OPTIONS, TRACE//HTTP 1.1
    }

    const string body;
    string url;
    _method method;
    string version;
    map<string, string> header;
    

public:
    HttpRequest();
    ~HttpRequest();
}
