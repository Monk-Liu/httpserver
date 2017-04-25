#include "httprequest.h"

/*  const string body;
    string method;
    string path;
    string version;
    map<string, string> header;
    map<string, string> args;
    bool keep_alive;
*/
int HttpRequest::parse_headers(string &str){
    if(str.empty()){
        return -1;
    }
    vector<string> res = split(str,"\r\n");
    //pv(res);
    int str_size = str.size();
    int flag =1;
    size_t pos;
    string key, val;
    for(vector<string>::iterator it=res.begin(); it!=res.end(); it++){
        if(flag){
            if(it->empty()){
                flag = 0;
            }else{
                if((pos=it->find(":"))!=string::npos){
                    key = it->substr(0,pos);
                    val = it->substr(pos+1);
                    if(key=="Connection" && val=="keep-alive"){
                        keep_alive = true;
                    }
                    headers.insert(pair<string, string>(key,val));
                }else{
                    cout<<"error at parse headers:"<<*it<<endl;
                    continue;
                }
            }
        }else{
            //cout<<"setbody"<<endl;
            body = *it;
        }
    }

    return 0;
}

int HttpRequest::parse_basic(string &str){
    if(str.empty()){
        return -1;
    }
    vector<string> res = split(str, " ");//copy构造函数和 copy赋值函数 
    if(res.size()==3){
        method = res[0];
        parse_path(res[1]);
        version = res[2];
    }else if(res.size()==2){
        method = res[0];
        parse_path(res[1]);
    }else{
        return -1;
    }
    return 0;
}

int HttpRequest::parse_args(string & str){
    if(str.empty()){
        return -1;
    }
    //先替换转义字符串, 然后处理参数 
    return 0;
}

int HttpRequest::parse_path(string & str){
    string tpath(""), query(""); //what is tpath used for? why not path=subresult?
    size_t pos;
    if((pos = str.find('?'))!=string::npos){
        query = str.substr(pos+1);
        parse_args(query);
    }
    tpath = str.substr(0, pos);
    path=tpath;
    return 0;
}

HttpRequest::HttpRequest(string &str){

    int pos = str.find("\r\n");
    int status = -1;
    //Question:parse_basic(str.substr(pos)); return error?
    if(pos!=string::npos){
        ok = true;
        string tmp = str.substr(0,pos);
        /* Question:
        * string::substr(size_t pos = 0, size_t len = npos);
        * 定义的时候, 默认参数右边必定是默认参数
        *
        * 调用的时候, 默认参数必须按顺序赋值,不能跳过其中一个?????这个设计不好吧?
        * */
        status = parse_basic(tmp);
        if(status<0){
            //error
        }
        tmp = str.substr(pos+2);
        status = parse_headers(tmp);
        if(status<0){
            //error;
        }
    }else{
        ok = false;
        cout<<"get the end"<<endl;
    };
}

HttpRequest::~HttpRequest(){
    
}

const string & HttpRequest::getmethod(){
    return method;
};
const string & HttpRequest::getpath(){
    return path;
};
const string & HttpRequest::getversion(){
    return version;
};
const map<string, string> & HttpRequest::getheaders(){
    return headers;
};
const map<string, string> & HttpRequest::getargs(){
    return args;
};
const bool HttpRequest::is_alive(){
    return keep_alive;
}
const string & HttpRequest::getbody(){
    return body;
}

