#ifndef MYTASK_H
#define MYTASK_H 1
//typedef void (*p)() funcp; //TODO

class MyTask{
public:
    //MyTask();
    int num;
    virtual void run()=0;
};

#endif
