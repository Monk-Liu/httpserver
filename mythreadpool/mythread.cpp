#include "mythread.h"
#include "mythreadpool.h"

int MyThread::backtoidle(){
    //cout<<"begine"<<endl;
    this->threadpool->removefrombusythreadpool(this);
    //cout<<thread_id<<" remove from busy"<<endl;
    this->threadpool->addtoidlethreadpool(this);
    //cout<<thread_id<<" add to idle"<<endl;
    return 0;
}

//实现第staitc方法的时候, 不用 再写static
int MyThread::threadfunc(MyThread * mt){
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 100000;
    while(1){
        if(mt->iskill()){
            break;
        }
        if(mt->task){
            mt->task->run();
            //cout<<"in thread "<<mt->thread_id<<" run the task "<<mt->task->num<<endl;
            delete mt->task;
            mt->task = NULL;
            mt->backtoidle();//这个地方,放回去之后, 马上拿出来用, 导致新的任务赋值之后, 又成了NULL; F***;
            //mt->task = NULL;
        }else{
            //nanosleep(&ts, NULL);
        }
    }

    return 0;
}

MyThread::MyThread(MyThreadPool *arg_threadpool){
    task = NULL;
    kill = false;
    threadp = new thread(threadfunc, this);
    threadp->detach(); //对于detch 的线程 valgrind　leak-check　的时候会有些问题
    thread_id = threadp->get_id();//对于不是joinable 的线程, get_id返回一个默认的构造函数的结果
    threadpool = arg_threadpool;
}

int MyThread::assign(MyTask * arg_task){
    if(arg_task){
        //cout<<"task "<<arg_task->num<<" is assign to "<<thread_id<<endl;
    }else{
        //cout<<"NULL task?"<<endl;
    }
    task = arg_task;
}

bool MyThread::iskill(){
    return kill;
}

thread::id MyThread::getthreadid(){
    return thread_id; 
}

void MyThread::finishtask(){
    task = NULL;
}

MyThread::~MyThread(){
    kill = true;
    //cout<<thread_id<<" is deleted"<<endl;
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 250000000;
    nanosleep(&ts,NULL);
    //delete threadp;
}
