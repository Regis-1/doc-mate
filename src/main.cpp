#include "server.h"
#include <iostream>

int main(int argc, char **argv) {
  std::cout << "Hello in Doc-Mate...\n";

  Server srv("127.0.0.1", 8089, 5);
  srv.bindSocket();
  srv.listenOnSocket();

  std::cout << "Finishing work...\n";
  return 0;
}
