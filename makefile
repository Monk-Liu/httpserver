test: myserver.cpp perror.cpp
	g++ myserver.cpp perror.cpp -o a

clean:
	rm a
