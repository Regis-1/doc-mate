all: server

server: server_main.o
	g++ -o server server_main.o

server_main.o: server_main.cpp
	g++ -c server_main.cpp

PHONY: clean
clean:
	rm server_main.o server
