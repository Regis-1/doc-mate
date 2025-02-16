ROOT_DIR = /home/regis/dev/doc-mate
SRC_DIR = /home/regis/dev/doc-mate/src
INC_DIR = /home/regis/dev/doc-mate/include

CXX = g++

export ROOT_DIR
export SRC_DIR
export INC_DIR

all: doc_mate

doc_mate:
	@$(MAKE) -C $(SRC_DIR);
	@echo "Building finished.";
