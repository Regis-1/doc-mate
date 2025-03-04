#include "server.h"
#include <unistd.h>
#include <iostream>

struct Options {
  bool serverMode {false};
  std::string ip;
  std::string indexDir;
};

void parseArgs(int argc, char **argv, Options &opts) {
  int opt;
  while ((opt = getopt(argc, argv, "s:")) != -1) {
    switch (opt) {
    case 's':
      std::cout << "1\n";
      opts.serverMode = true;
      std::cout << "2\n";
      opts.ip = optarg;
      std::cout << "3\n";
      break;
    default:
      std::cerr << "Usage: " << argv[0] << " [-s ip] index_dir\n";
      exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    std::cerr << "Expected argument after options\n"
	      << "Usage: " << argv[0] << " [-s ip] index_dir\n";
    exit(EXIT_FAILURE);
  }

  opts.indexDir = argv[optind];
}

int main(int argc, char **argv) {
  Options options;
  
  std::cout << "Hello in Doc-Mate...\n";
  parseArgs(argc, argv, options);

  if (options.serverMode) {
    // server mode
    Server srv(options.ip, 8089, 5);
    srv.bindSocket();
    srv.listenOnSocket();
  }
  else {
    // local / terminal mode
    std::cout << "Going with terminal mode...\n";
  }

  std::cout << "Finishing work...\n";
  return 0;
}
