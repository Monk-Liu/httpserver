#include "test.h"
#include <stdlib.h>

const static int SIZE=20;

class workthd:public MyTask{
    int no;
public:
    workthd(int i){
        no = i;
        num = i;//num在父类中声明
    }
    void run(){
        cout<<"This is "<<no<<" task"<<endl;
    }
};

int main(int argc, char ** argv){
    MyThreadPool mtp(2);
    int size;
    if(argc == 2){
        size = atoi(argv[1]);
    }else{
        size = SIZE;
    }
    workthd* wl[size];

    for(int i=0; i<size; i++){
        wl[i] = new workthd(i);
        mtp.addtask(wl[i]);
    }

    mtp.wait();
    return 0;
}
