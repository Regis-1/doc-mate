all: main.o server.o
	@$(CXX) -o $(ROOT_DIR)/doc-mate $^;

main.o: main.cpp
	@$(CXX) -c $^ -I$(INC_DIR);

server.o: server.cpp
	@$(CXX) -c $^ -I$(INC_DIR);
