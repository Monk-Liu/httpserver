#include "httphandler.h"
#include <iomanip>

void HttpHandler::run(){
    HttpRequest req(reqstr);
    if(req.ok){
        HttpResponse res(skfd);
        Application app(req, res);
    }else{
        cout<<"exit"<<endl;//为什么会退出?
    }
    //return res.getresponse();
    delete skfd;
    return ;
}

HttpHandler::HttpHandler(MySocket * arg_skfd, string arg_str){
    skfd = arg_skfd;
    reqstr = arg_str;
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
