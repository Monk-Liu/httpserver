#ifndef MYTHREADPOOL_H
#define MYTHREADPOOL_H
#include "mythread.h"
#include "mytask.h"
#include <mutex>
#include <vector>
#include <queue>

using namespace std;
class MyThreadPool{
    const int SIZE;
    const int MINSIZE;
    const int MAXSIZE;
    vector<MyThread *> idlethreadpool;
    vector<MyThread *> busythreadpool;
    queue<MyTask *> taskpool;
    mutex busy_mutex;
    mutex idle_mutex;
    mutex task_mutex;
    thread * threadp;
    bool kill;
public:
    MyThread* getidlethread();
    int addnewidlethread();
    int addtobusythreadpool(MyThread * );
    int addtoidlethreadpool(MyThread * );
    int removefrombusythreadpool(MyThread *);
    int addtask(MyTask *);
    MyTask * gettask();
    int tasksize();
    int busysize();
    static void threadfunc(MyThreadPool *);
    bool iskill();
    void stop();
    void wait();

    MyThreadPool(int);
    ~MyThreadPool();
};

#endif
