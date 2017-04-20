#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(){
    
    string path = "/home/liuqifan/Lab/Net/HttpServer/static/a";

    ifstream fd(path.c_str());

    if(fd.is_open()){
        char buffer[101];
        int n;
        while(!(fd.eof())){
            //cout<<fd<<endl;
            //fd.seekg(0, ios::beg);
            n = fd.read(buffer, 100);
            cout<<n<<endl;
            buffer[n] = '\0';
            cout<<string(buffer)<<endl;;
            //cout<<buffer[28]<<endl;
            //cout<<buffer[27];
        }
    }
    
}
