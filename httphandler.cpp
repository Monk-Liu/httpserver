#include "httphandler.h"
#include <iomanip>

string HttpHandler::handler(MySocket*skfd,string  str){
    HttpRequest req(str);
    HttpResponse res(skfd);
    cout<<"start process"<<endl;
    Application app(req, res);
    
    cout<<"finish"<<endl;

    //return res.getresponse();
    return "aaa";
}

HttpHandler::HttpHandler(){

}

HttpHandler::~HttpHandler(){

}





//int main(){
//    string httpstr = "GET /path HTTP/1.0\r\nContent-Type:text/html\r\n\r\naaaaaa";
//    HttpRequest req(httpstr);
//
//    cout<<setfill(' ')<<setw(13)<<"Method:"<<req.getmethod()<<endl;
//    cout<<setfill(' ')<<setw(13)<<"Path:"<<req.getpath()<<endl;
//    cout<<setfill(' ')<<setw(13)<<"Version:"<<req.getversion()<<endl;
//    map<string, string> hd = req.getheaders();
//
//    for(map<string, string>::iterator it=hd.begin(); it!=hd.end(); ++it){
//        cout<<setfill(' ')<<setw(13)<<"Header:"<<it->first<<":"<<it->second<<endl;
//    }
//    cout<<setfill(' ')<<setw(13)<<"Body:"<<req.getbody()<<endl;
//
//    return 0;
//}
