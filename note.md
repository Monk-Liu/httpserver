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
 
 2.官方filesystem 链接库的时候, 貌似之前已经安装过那个库, 导致一直再用之前的版本1.60.0, 而这个版本和1.48 差别很大, 导致 -lboost_filesystem不对