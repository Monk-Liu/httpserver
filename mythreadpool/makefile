main: test.o mythread.o mytask.o mythreadpool.o
	g++ test.o mythread.o mytask.o mythreadpool.o -o a -pthread -std=c++11 -Wall -g

mythread.o: mythread.cpp mytask.h
	g++ -c mythread.cpp -g

mytask.o: mytask.h
	g++ -c mytask.cpp -g

mythreadpool.o: mythreadpool.cpp mythread.h mytask.h
	g++ -c mythreadpool.cpp -g

test.o: test.cpp mythread.h mythreadpool.h mytask.h
	g++ -c test.cpp -g
