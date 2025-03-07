
GTEST_DIR = $(ROOT_DIR)/extlibs/googletest/build
LDFLAGS = -L$(GTEST_DIR)/build/lib -lgtest

all: parserTests.o
	@mkdir -p bin
	@$(CXX) -o bin/parserTests $(LDFLAGS) $^;

parserTests.o: parserTests.cpp
	@$(CXX) $(CXXFLAGS) -c $^;

.PHONY: clean
clean:
	@rm -r bin *.o
