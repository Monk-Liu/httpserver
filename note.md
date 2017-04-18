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

+ SO_REUSEPORT / SO_REUSEADDR [reference](http://stackoverflow.com/questions/14388706/socket-options-so-reuseaddr-and-so-reuseport-how-do-they-differ-do-they-mean-t)