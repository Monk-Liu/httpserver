#include "app.h"
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

const static string ROOT = "./static";
const static char * NOTFOUND = "./static/404.html";

Application::Application(HttpRequest &req, HttpResponse &res){
    cout<<"start handler"<<endl;
    handler(req,res);
    cout<<"end handler"<<endl;
}

int Application::handler(HttpRequest &req, HttpResponse &res){

    string p_str = ROOT+req.getpath(); //过滤 ..
    const char * p_char = p_str.c_str();
    //cout<<path_str<<endl;
    path p(p_str.c_str());
    if(exists(p)){
        if(is_regular_file(p)){
            ifstream fd;
            //cout<<path_str<<endl;  //the path_str is not the same as line 18;
            fd.open(p_char);
            cout<<p_char<<endl;
            cout<<"file open"<<fd.is_open()<<endl;
            if(!(fd.is_open())){
                return 0;
            }
            cout<<"file open"<<endl;
            string key, value;
            key = "Content-Type";
            value = "text/html"; //MIME TYPE
            res.setHeader(key,value);
            long len;
            len = file_size(p);
            /*fd.seekg(0, ios::end);
            len = fd.tellg();
            fd.seekg(0, ios::beg);a*/
            res.setDataLen(len);
            //redds.setHeader("Content-Length",string(len_cha));
            char buffer[100];
            string wbuf;
            while(!(fd.eof())){
                fd.read(buffer,100);  
                wbuf = string(buffer);  //mywrite -> string -> char *;
                res.writeData(wbuf);
                cout<<"in while loop"<<endl;
                cout<<fd.eof()<<endl;
            }
            cout<<"file close"<<endl;
            fd.close();
        }else if(is_directory(p)){
            vector<path> v;
            string body="<html><body><h2>" + string(p_char) + "</h2><ul>";
            string key, value;
            copy(directory_iterator(p), directory_iterator(), back_inserter(v));

            for(vector<path>::iterator it=v.begin(); it!=v.end(); it++){
                body = body + "<li><a href=\""+ (it->c_str()+9)+ "\">" +it->filename().c_str()+ "</a></li>";
            }
            body = body+"</ul></body></html>";

            key = "Content-Type";
            value = "text/html";
            res.setHeader(key,value);
            long len = body.size();
            res.setDataLen(len);
            
            res.writeData(body);
        }
    }else{
        cout<<"file not found"<<endl;
        ifstream fd;
        fd.open(NOTFOUND);
        cout<<"file is open:"<<fd.is_open()<<endl;
        if(!fd.is_open()){
            return 0;
        }
        string key, value;
        key = "Content-Type";
        value = "text/html"; //MIME TYPE
        res.setHeader(key,value);
        res.setStatus(404);
        long len;
        fd.seekg(0, ios::end);
        len = fd.tellg();
        fd.seekg(0, ios::beg);
        res.setDataLen(len);
        //redds.setHeader("Content-Length",string(len_cha));
        char buffer[100];
        string wbuf;
        while(!(fd.eof())){
            fd.read(buffer,100);  
            wbuf = string(buffer);  //mywrite -> string -> char *;
            res.writeData(wbuf);
            cout<<"in while loop"<<endl;
        }
        cout<<"file close"<<endl;
        fd.close();
    }


}

