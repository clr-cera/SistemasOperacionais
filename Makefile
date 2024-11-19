client:
	g++ -c ./src/client.cpp
	g++ *.o -o client
	rm *.o

server:
	g++ -c ./src/server.cpp
	g++ *.o -o server
	rm *.o

zip:
	zip -R trabalhoSO.zip . '*.c' '*.cpp' '*.h' 'Makefile'
