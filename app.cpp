#include "app.h"
const static string ROOT = "/home/liuqifan/Lab/Net/HttpServer/static";

Application::Application(HttpRequest &req, HttpResponse &res){
    cout<<"start handler"<<endl;
    handler(req,res);
    cout<<"end handler"<<endl;
}

int Application::handler(HttpRequest &req, HttpResponse &res){

    string path = ROOT+req.getpath();
    cout<<req.getpath()<<endl;
    cout<<path<<endl;
    ifstream fd(path.c_str());
    //fd.open(path.c_str());
    if(fd.is_open()){
        cout<<"file open"<<endl;
        string key, value;
        key = "Content-Type";
        value = "text/html";
        res.setHeader(key,value);
        long len;
        fd.seekg(0, ios::end);
        len = fd.tellg();
        fd.seekg(0, ios::beg);
        //res.setHeader("Content-Length",string(len_cha));
        res.setDataLen(len);

        char buffer[100];
        string wbuf;
        while(!(fd.eof())){
            fd.read(buffer,100);  
            wbuf = string(buffer); 
            res.writeData(wbuf);
            cout<<"in while loop"<<endl;
        }
        cout<<"file close"<<endl;
        
        fd.close();
    }else{
        cout<<"file not open"<<endl;
    }


}

