#include "httpresponse.h"
/*
    int datalen;
    map<string, string> headers;
    string version;
    int status;
    string reason;
    bool headflag; //写data之前数据有没有写?
    const MySocket* skfd
*/
    
int HttpResponse::addHeader(string & key, string &val){
    if(headers.find(key) == headers.end()){
        return -1;
    }
    headers[key] = val;
    return 0;
};

int HttpResponse::setHeader(string & key, string &val){
    cout<<"setHeader:"<<key<<val<<endl;
    headers[key] = val;
    return 0;
};

int HttpResponse::setStatus(int arg_status=200){
    status = arg_status;
    switch(status/100){
        case 1:
            reason = "Connect";
        case 2:
            reason = "OK";
        case 3:
            reason = "move";
        case 4:
            reason = "clienterror";
        default:
            reason = "servererror";
    }
    return 0;
};

int HttpResponse::setVersion(string arg_version="HTTP/0.9"){
    cout<<"setVersion:"<<arg_version<<endl;
    version = arg_version ;
    return 0;
};

int HttpResponse::setDataLen(long arg_dlen){
    datalen = arg_dlen;
    cout<<"setDataLen:"<<arg_dlen<<endl;
    char str_len[15];
    sprintf(str_len,"%ld",datalen);
    cout<<"datalen is"<<string(str_len)<<endl;
    headers["Content-Length"] = string(str_len);
    return 0;
};

int HttpResponse::writeData(string & buffer){
    cout<<"writeData:"<<buffer<<endl;
    if(headflag){
        skfd->mywrite(buffer);
    }else{
        writeHeader();
        cout<<"write head finished"<<endl;
        skfd->mywrite(buffer);
    }
    cout<<"write data finish"<<endl;
};

int HttpResponse::writeHeader(){
    //char tmp_buf[5];
    //sprintf(tmp_buf,"%d",status);
    //string status_str(tmp_buf);
    string status_str="200";
    string tag;
    tag.append(version);
    tag.append(" ");
    tag.append(status_str);
    tag.append(" ");
    tag.append(reason);
    tag.append("\r\n");

    skfd->mywrite(tag);

    string wbuff;
    for(map<string, string>::iterator it=headers.begin(); it!=headers.end(); ++it){
        wbuff = wbuff + it->first;
        wbuff = wbuff + ":";
        wbuff = wbuff + it->second;
        wbuff = wbuff + "\r\n";
        cout<<"write head:"<<wbuff;
        skfd->mywrite(wbuff);
        wbuff.clear();
    }
    string crlf = "\r\n";
    skfd->mywrite(crlf); 
    cout<<"int writeheader finished"<<endl;
    headflag = true;
    return 0;
};

int HttpResponse::finish(){};

HttpResponse::HttpResponse(MySocket * arg_skfd):skfd(arg_skfd){
    headflag = 0;
    status = 200;
    reason = "OK";
    version = "HTTP/1.0";
}
HttpResponse::~HttpResponse(){};


/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    string data = "this is data";
    int fd = open("./fileout",O_RDWR|O_TRUNC);
    MySocket msk(fd);
    HttpResponse res(&msk);
    res.writeHeader();
    res.writeData(data);
    return 0;

}*/
