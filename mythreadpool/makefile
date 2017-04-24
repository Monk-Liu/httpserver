main: test.o mythread.o mytask.o mythreadpool.o
	g++ test.o mythread.o mytask.o mythreadpool.o -o a -pthread -std=c++11 -Wall -g

mythread.o: mythread.cpp mytask.h
	g++ -c mythread.cpp

mytask.o: mytask.h
	g++ -c mytask.cpp

mythreadpool.o: mythreadpool.cpp mythread.h mytask.h
	g++ -c mythreadpool.cpp

test.o: test.cpp mythread.h mythreadpool.h mytask.h
	g++ -c test.cpp
