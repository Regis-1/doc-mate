all: main.o server.o
	@$(CXX) -o $(ROOT_DIR)/doc-mate $^;

main.o: main.cpp
	@$(CXX) $(CXXFLAGS) -c $^;

server.o: server.cpp
	@$(CXX) $(CXXFLAGS) -c $^;

.PHONY: clean
clean:
	@rm *.o $(ROOT_DIR)/doc-mate;
