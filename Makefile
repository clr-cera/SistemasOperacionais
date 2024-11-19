all: client server
	echo 'Compiled!'

run_server: server
	./server

run_server_nohup: server
	nohup ./server &

run_client: client
	./client

client: clientObj
	g++ *.o -o client
	rm *.o

server: serverObj
	g++ *.o -o server
	rm *.o

clientObj:
	g++ -c ./src/client.cpp

serverObj:
	g++ -c ./src/server.cpp

clean:
	rm *.o *.zip server client

zip:
	zip -R trabalhoSO.zip . '*.c' '*.cpp' '*.h' 'Makefile'
