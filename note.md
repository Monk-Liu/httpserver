+ socket 中bind用到的 [sockaddr/sockaddr_in](http://beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html)

+ port和server地址  hton, gethostbyname转换

+ read/write 函数的处理: 
1.getline需要 iostream的参数, 需要从int类型的句柄构造iostream
2.直接用while加 read/write

+ string和char* 类转换
string->char *
		  
		  string str = "some string" ;
		  char *cstr = &str[0u];
char * ->string

		  string str(char *)
		  // str.append(char *
		  
+ postman cancel之后不能 服务器就不能继续建立连接
	accept: Invalid argument;

+ SO_REUSEPORT / SO_REUSEADDR [reference](http://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t)
also [another sorequest](https://lwn.net/Articles/542629/)


+ [guide](https://www.scribd.com/document/120274805/QGNPs)

+ [split in c++](http://stackoverflow.com/questions/236129/split-a-string-in-c)
1. boost
2. self define

+ 内存溢出 core dump, 
gdb调试 g++编译的时候加 -g选项, 在gdb里面可以进入函数, 看见代码
s 跳入函数, finish跳出, print显示
然后在单步执行的时候发现 writeHeader函数 return之后, 跳转到 内部的一个地址(某个函数吧栈中返回地址复写了)
继续追查发现是MySocket::mywrite函数里面,用了memcpy cpoy一个string的引用的时候,吧 writeHeader栈内变量内容覆写了
这个问题有由于 writesize, 这个临时变量没有处理好
由此: 以后出现这种问题, 主要查看 有memcpy, alloc relloc这这种内存操作的地方!!!

+ core dump munmap_chunk(): Invaild pointer;
这个内存泄露是 free一个无效指针,在MySocket::myread中, 用了string::append导致了这个错误
联想到是不是,在append的过程中, 会检测参数是否在堆中, append的参数在堆中会释放那块内存, 导致while循环第二次append的时候出错?
然后吧buffer定义在栈中, 没有这个问题了???
很迷  //TODO

+ 检查了一个晚上的 内存冲突问题, 居然是
 new char(BUFFSIZE)导致的
 ---> new char[BUFFSIZE]
 
 + valgrind  内存检查
 
 + vector [详细](http://blog.csdn.net/hancunai0017/article/details/7032383)
 
 + boost库安装的时候出了很多fail(导致后面碰到问题的时候我都以为是编译的时候出错了, 其实并不是)
 问题是:
 1.官方程序 lambda 编译出错 lambda::detail::operator_return_type..... template 出错argument错误  //TODO
 2.官方filesystem 链接库的时候, 貌似之前已经安装过那个库, 导致一直再用之前
的版本1.60.0, 而这个版本和1.48 差别很大, 导致 -lboost_filesystem不对
 + boost::filesystem::path问题:
 
 		   const char * path_char = "/statis";
 		   const char * p_char = p_str.c_str();
    		  //cout<<path_str<<endl;
		    path p(p_str.c_str());
		    if(exists(p)){
			if(is_regular_file(p)){
			    ifstream fd;
			    //cout<<path_str<<endl;  //the path_str is not the same as line 18;
			    fd.open(p_char);
			    cout<<p_char<<endl;
			    
+ boost::filesystem::copy 怎么实现的? 为什么下面的代码就能实现遍历?

            copy(directory_iterator(p), directory_iterator(), back_inserter(v));

+ 感觉boost库用起来没有 标准的那么舒服,  还是自己调系统接口来的直接?

+ select pool 用法 三个FD_SET 具体有待研究! //TODO

+ threadpool  实现方法; pool对队列管理, 自定义可以assign任务的mythread, 继承task类; virtual的动态绑定!!!

+ namespace 是标识符可见范围;
c++标准库都定义在std中;
namespace提出, 主要是为了解决命名冲突的问题!

+ C++ 解决两个类[互相引用](http://www.cnblogs.com/zendu/p/4987971.html)的方法: A.h里面引用B.h, B.h 定义 class A; , B.cpp里引用A.h
但是, 为什么这样不会出现类的多次定义?

+ C++11 不能定义 void的成员函数?
实际上是, 返回为void的函数, void要显示定义

+ 对, thread(threadfunc, this)的时候, 报错

		  invalid use of non-static member function
		  
当时用吧方法改成static解决这个问题, 但是? stackoverflow上有对这个问题深一点的[讨论](http://stackoverflow.com/questions/29286863/invalid-use-of-non-static-member-function

+ cpp 居然不能在全局里面定义执行语句?)

+ 在 join之前调用～Thread() 导致

		　　terminate called without an active exception

设置为　detach模式可以解决这个问题． why?

		 id get_id() const noexcept;
		 Get thread id
		 Returns the thread id.
		 If the thread object is joinable, the function returns a value that uniquely identifies the thread.
		 If the thread object is not joinable, the function returns a default-constructed object of member type thread::id.
		 
+ valgrind leak-check 和　thread detach　之间的[问题](http://stackoverflow.com/questions/20893358/a-detached-pthread-causes-memory-leaks)．

+ 加入了threadpool, 然而发现用本机测试
	
		 ab -n 10000 -c 1000 127.0.0.1:8080/a
		 
 没有加入线程池的反而更快! 0.9 : 19s
 
 +  而且, 1 构建handler的时候,  string参数没有传入, 导致request构造失败??
 +  然后, 写mythread的时候,  循环处理的函数threadfunc在处理的时候, 如果没有检测到任务会延迟0.25s再检测, 这个检测在并发的时候很关键! 吧0.25s改为0.1ms, 直接吧 10000个请求 1000并发, 时间从32降到了19;
 
 + 好的, 告一段落, select