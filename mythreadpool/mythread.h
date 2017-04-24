#ifndef MYTHREAD_H
#define MYTHREAD_H 1
#include "mytask.h"
#include <thread>
#include <time.h>
#include <iostream>

using namespace std;



class MyThreadPool;

class MyThread{
    thread * threadp;
    MyThreadPool * threadpool;
    bool kill;

public:
    thread::id thread_id;
    MyTask * task;
    MyThread(MyThreadPool *);
    int assign(MyTask * arg_task);
    thread::id getthreadid();
    //int run();
    ~MyThread();
    int backtoidle();
    static int threadfunc(MyThread *);
    void test();
    bool iskill();
    void finishtask();
};

#endif
