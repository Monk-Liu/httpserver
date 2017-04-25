#include "mysocket.h"

MySocket::MySocket(int arg_skfd, struct sockaddr * arg_sa):skfd(arg_skfd),BUFFSIZE(100){
    bcopy((char *)arg_sa, (char *)&sa, sizeof(struct sockaddr));
    buffer = new char[BUFFSIZE];
}

MySocket::MySocket(int arg_skfd):skfd(arg_skfd),BUFFSIZE(100){
    buffer = new char[BUFFSIZE];
}

int MySocket::myread(string& rbuff){
    int res=0;
    int n=0;
    char buffer[BUFFSIZE];
    do{
        n = read(skfd, buffer, BUFFSIZE);
        res+=n;
        rbuff.append(buffer, n);

    }while(n==BUFFSIZE);


    return res;
}

int MySocket::mywrite(char* wbuff, int len){
    if(len>100){
        cout<<"len > 100"<<endl;
    }else{
    }
    int res=0;
    int n=1;
    int bsize = len;
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
        //cout<<bsize<<";"<<res<<endl;
        //cout<<writesize<<endl;
        //memcpy(buffer,wbuff+res,writesize);
        write(skfd, wbuff+res, writesize);
        res+=writesize;
        n++;
    }while(!flag);

    return res;
}

int MySocket::mywrite(string& wbuff){
    int res=0;
    int n=1;
    int bsize = wbuff.size();
    const char * wbuff_str = wbuff.c_str();
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
        if(writesize>BUFFSIZE){
            cout<<bsize<<";"<<res<<";"<<endl;
        }
        //cout<<writesize<<endl;
        memcpy(buffer,wbuff_str+res,writesize);
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
