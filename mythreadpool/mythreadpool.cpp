#include "mythreadpool.h"

MyThreadPool::MyThreadPool(int n):MINSIZE(1),SIZE(n),MAXSIZE(4*n){
    kill = false;
    for(int i=0; i<SIZE; i++){
        addnewidlethread();
    } 
    threadp = new thread(threadfunc, this);
    threadp->detach();
}

MyThread * MyThreadPool::getidlethread(){
    MyThread * mt;
    int size;
    idle_mutex.lock();
    size = idlethreadpool.size();
    idle_mutex.unlock();

    if(size>=MINSIZE){
        idle_mutex.lock();
        mt = idlethreadpool.back();
        idlethreadpool.pop_back();
        idle_mutex.unlock();
    }else{
        busy_mutex.lock();
        size = busythreadpool.size();
        busy_mutex.unlock();
        if(size>=MAXSIZE){
            mt = NULL;
        }else{
            addnewidlethread();
            idle_mutex.lock();
            mt = idlethreadpool.back();
            idlethreadpool.pop_back();
            idle_mutex.unlock();
        }
    }
    return mt;
}

int MyThreadPool::addnewidlethread(){
    idle_mutex.lock();
    idlethreadpool.push_back(new MyThread(this));
    idle_mutex.unlock();
    return 0;
}

int MyThreadPool::addtobusythreadpool(MyThread *arg_thread){
    busy_mutex.lock();
    busythreadpool.push_back(arg_thread);
    busy_mutex.unlock();
    return 0;
}

int MyThreadPool::addtoidlethreadpool(MyThread * arg_thread){
    idle_mutex.lock();
    //这里检测空闲线程是否太多
    idlethreadpool.push_back(arg_thread);
    idle_mutex.unlock();
    return 0;
}

int MyThreadPool::removefrombusythreadpool(MyThread *arg_thread){
    busy_mutex.lock();
    int i=0;
    int len = busythreadpool.size();
    for(;i<len;i++){        
        if(busythreadpool[i] == arg_thread){
            break; 
        }
    }
    if(i!=len){
        busythreadpool.erase(busythreadpool.begin()+i);
    }else{
    }
    if(arg_thread->task){
        //cout<<arg_thread->task->num<<" removed"<<endl;
    }else{
        //cout<<"remove task is null"<<endl;
    }
    busy_mutex.unlock();
    return 0;
}

int MyThreadPool::addtask(MyTask * arg_task){
    //MyThread * mt = getidlethread();
    //mt->assign(arg_task);
    //addtobusythreadpool(mt);

    task_mutex.lock();
    taskpool.push(arg_task);
    task_mutex.unlock();
    return 0;
}

MyThreadPool::~MyThreadPool(){
    //怎么清? 
    kill = true;
    this->stop();
    //cout<<"another end"<<endl;
    //等所有都运行完 //如果线程卡住了怎么办?
    for(int i=0; i<idlethreadpool.size(); i++){
        delete idlethreadpool[i];
    }
    //delete threadp; //detach 的线程不用别的释放资源
    //cout<<"finish"<<endl;
}

MyTask *MyThreadPool::gettask(){
    MyTask * mta;
    task_mutex.lock();
    //考虑两个线程同时查到 size =1;
    if(taskpool.size()){
        mta = taskpool.front();
        taskpool.pop();
    }else{
        mta = NULL;
    }

    task_mutex.unlock();
    return mta;
}

int MyThreadPool::tasksize(){
    //查大小就不加锁了, 在gettask里解决冲突
    return taskpool.size();
}

int MyThreadPool::busysize(){
    return busythreadpool.size();
}

void MyThreadPool::stop(){
    //cout<<"start stop"<<endl;
    kill = true;
    while(1){
        if(busysize()){
            continue;
        }else{
            break;
        }
    }
    //cout<<"end stop"<<endl;
}

void MyThreadPool::wait(){
    int count = 0;
    while(1){
        if(tasksize()|| busysize()){
            count++;
            //cout<<tasksize()<<";"<<busysize()<<endl;
            if(count>300000){
                count = 0;
                busy_mutex.lock();
                for(int i=0; i<busysize(); i++){
                    if(busythreadpool[i]->task){
                        //cout<<"task "<<busythreadpool[i]->task->num<<" is busy"<<endl;
                    }else{
                        //cout<<"busy thread "<<busythreadpool[i]->thread_id<<" task is null"<<endl;
                        //cout<<"i is "<< i<<endl;
                    }
                }
                busy_mutex.unlock();
            }
            continue;
        }else{
            break;
        }
    }
}


bool MyThreadPool::iskill(){
    return kill;
}

void MyThreadPool::threadfunc(MyThreadPool * mtp){
    while(1){
        if(mtp->iskill()){
            if(mtp->busysize()){
                continue;
            }else{
                //cout<<"thread func end"<<endl;
                break;
            }
        }
        MyTask * mta;
        MyThread * mt;
        if(mtp->tasksize()){
            //很奇怪, 为什么还要查一下size? 为什么不直接取???? 没必要查size的->可以避免频繁lock/unlock? 有必要吗?
            mta = mtp->gettask();
            if(mta){
                //cout<<"task "<<mta->num<<" is assign to "<<mt->thread_id<<endl;
                do{
                    mt = mtp->getidlethread();
                }while(mt==NULL);
                mt->assign(mta); 
                mtp->addtobusythreadpool(mt);
            }
        }   
    }
}
