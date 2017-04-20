test: myserver.o perror.o mysocket.o httpresponse.o httprequest.o httphandler.o myutill.o app.o 
	g++ myserver.o mysocket.o httphandler.o httpresponse.o httprequest.o app.o perror.o myutill.o -o a.o -g


myserver.o: myserver.cpp mysocket.h httphandler.h perror.h
	g++ -c myserver.cpp 


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
	g++ -c httprequest.cpp

app.o: app.cpp httprequest.h httpresponse.h
	g++ -c app.cpp

clean:
	rm *.o
