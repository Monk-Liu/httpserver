#include "mysocket.h"

MySocket::MySocket(int arg_skfd, struct sockaddr * arg_sa):skfd(arg_skfd),BUFFSIZE(100){
    bcopy((char *)arg_sa, (char *)&sa, sizeof(struct sockaddr));
    buffer = new char(BUFFSIZE);
}

MySocket::MySocket(int arg_skfd):skfd(arg_skfd),BUFFSIZE(100){
    buffer = new char(BUFFSIZE);
}

int MySocket::myread(string& rbuff){
    int res=0;
    int n=0;
    do{
        n = read(skfd, buffer, BUFFSIZE);
        res+=n;
        rbuff.append(buffer);

    }while(n==BUFFSIZE);


    return res;
}

int MySocket::mywrite(string& wbuff){
    int res=0;
    int n=1;
    int bsize = wbuff.size();
    const char * wbuff_char = wbuff.c_str();
    int writesize = 0;
    int flag;
    //res = getline(skfd, rbuff); getline 参数是一个fstream类, 然而skfd是int! 有什么通过int构建stream类的函数吗?
    do{
        flag = res+BUFFSIZE >bsize;
        if(flag){
            writesize = bsize-res;
        }else{
            writesize = BUFFSIZE;
        } 
        memcpy(buffer,wbuff_char+res,writesize);
        write(skfd, buffer, writesize);
        res+=writesize;
        n++;
    }while(!flag);

    return res;
}

MySocket::~MySocket(){
    close(skfd);
    delete[] buffer;//?? free in valid next size; 
}
