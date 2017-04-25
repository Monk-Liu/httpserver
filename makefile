CPPFLAGS=-Wall -std=c++11 -g
LDFLAGS=-pthread

test: myserver.o perror.o mysocket.o httpresponse.o httprequest.o httphandler.o myutill.o app.o main.o
	g++ main.o myserver.o mysocket.o httphandler.o httpresponse.o httprequest.o app.o perror.o myutill.o \
		mythreadpool/mythreadpool.o mythreadpool/mythread.o mythreadpool/mytask.o -o a.o \
		-lboost_system -lboost_filesystem  $(CPPFLAGS) $(LDFLAGS)


main.o: main.cpp mysocket.h httphandler.h myserver.h
	g++ -c main.cpp -g

myserver.o: myserver.cpp mysocket.h httphandler.h perror.h
	g++ -c myserver.cpp  -g


myutill.o: myutill.cpp
	g++ -c myutill.cpp 

perror.o: perror.cpp
	g++ -c perror.cpp

mysocket.o: mysocket.cpp
	g++ -c mysocket.cpp -g

httphandler.o: httphandler.cpp httpresponse.h httprequest.h app.h
	g++ -c httphandler.cpp

httpresponse.o: httpresponse.cpp mysocket.h
	g++ -c httpresponse.cpp -g

httprequest.o: httprequest.cpp
	g++ -c httprequest.cpp -g

app.o: app.cpp httprequest.h httpresponse.h
	g++ -c app.cpp -lboost_system -l boost_filesystem -g

mythreadpool.o: mythreadpool/mythreadpool.cpp mythreadpool/mythread.h mythreadpool/mytask.h 
	g++ -c mythreadpool/mythreadpool.cpp -g -pthread -std=c++11

mythread.o: mythreadpool/mythreadpool.h mythreadpool/mytask.h mythreadpool/mythread.cpp 
	g++ -c mythreadpool/mythread.cpp -g -pthread -std=c++11

mytask.o: mythreadpool/mytask.cpp
	g++ -c mythreadpool/mytask.cpp -g

clean:
	rm *.o
